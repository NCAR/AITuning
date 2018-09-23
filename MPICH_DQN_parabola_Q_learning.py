import numpy as np
import os.path
from collections import defaultdict
from math import floor
import random
from keras.models import model_from_json
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Conv1D
from keras.layers import advanced_activations
from keras import optimizers

n_control_vars = 6
n_performance_vars = 12

perf_var_names = [
"unexpected_recvq_length_avg",
"unexpected_recvq_length_max",
"num_procs_avg",
"num_procs_max",
"total_time_avg",
"total_time_max",
"put_time_avg",
"put_time_max",
"get_time_avg",
"get_time_max",
"flush_time_avg",
"flush_time_max",
]

control_var_names = [
"MPIR_CVAR_ASYNC_PROGRESS",
"MPIR_CVAR_CH3_ENABLE_HCOLL",
"MPIR_CVAR_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING",
"MPIR_CVAR_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE",
"MPIR_CVAR_POLLS_BEFORE_YIELD",
"MPIR_CVAR_CH3_EAGER_MAX_MSG_SIZE",
]

def _read_some_vars(raw_data, my_list, kind):
    my_vars = {}
    for entry in raw_data.split('\n'):
        if '=' in entry:
            name, value = entry.split('=')
            if name in my_list:
                my_vars[name] = kind(value)
    return my_vars

def _read_performance_vars(raw_data):
    return _read_some_vars(raw_data, perf_var_names, float)

def _read_control_vars(raw_data):
    return _read_some_vars(raw_data, control_var_names, int)

def write_changes(changes):
    file_object  = open('changes.txt', 'w')
    for j in range(len(changes)):
        file_object.write(control_var_names[j]+"="+str(changes[j])+"\n")

def read_replay(X,Y):
    if(not os.path.isfile('replay_X.txt')):
        return
    X = np.loadtxt('replay_X.txt', dtype=float)
    Y = np.loadtxt('replay_Y.txt', dtype=float)

def write_replay(X,Y):
    np.savetxt('replay_X.txt', X, fmt='%f')
    np.savetxt('replay_Y.txt', Y, fmt='%f')

def read_control_vars():
    return _read_control_vars(open('control_variables.txt', 'r').read())

def read_performance_vars():
    return _read_performance_vars(open('performance_variables.txt', 'r').read())

def read_old_performance_vars():
    return _read_performance_vars(open('old_performance_variables.txt', 'r').read())

def write_counter(counter):
    fileout = open("counter.txt", 'w')
    fileout.write(str(counter))

def read_counter():
    if(os.path.isfile("counter.txt")):
        counter = open("counter.txt", 'r').read()
    else:
        counter = 0
        write_counter(counter)
    return int(counter)

def check_reward(perf_var_list, np_performance_vars, new_perf_vars):
    reward = 0
    for i in range(n_performance_vars):
        list_names = list(perf_var_list.keys())
        if(list_names[i] == "total_time_avg"):
            print(str(i)+" Prev "+ str(np_performance_vars[i])+ " new "+str(new_perf_vars[i]))
            if(np_performance_vars[i] > new_perf_vars[i]):
                reward = reward + 20
            elif (np_performance_vars[i] == new_perf_vars[i]):
                pass
            else:
                reward = reward - 30

        if(list_names[i] == "total_time_max"):
            if(np_performance_vars[i] > new_perf_vars[i]):
                reward = reward + 5
            else:
                reward = reward - 3

        if(np_performance_vars[i] > new_perf_vars[i]):
            reward = reward + 3
        elif(np_performance_vars[i] < new_perf_vars[i]):
            reward = reward - 2
        if(np_performance_vars[i] == new_perf_vars[i]):
            reward = reward - 1
    print(reward)
    return reward

def make_epsilon_greedy_policy(model,epsilon,n_actions):
    
    def policy_fn(state):
        A = np.ones(n_actions, dtype=float) * epsilon / (n_actions)
        Y = model.predict(state)
        best_action = np.argmax(Y)
        A[best_action] += (1.0 - epsilon)
        return A
    return policy_fn

def select_next_action(model, next_state):
    Y = model.predict(next_state)
    best_action = np.argmax(Y)
    return best_action

def get_Q_value(X,action,model):
    Y = model.predict(X)
    return Y[0][action]

def get_Q_value_all_actions(X,model):
    Y = model.predict(X)
    return Y

def fromDictToNp(dict):
    alist = [float(v) for k,v in dict.items()]
    X = np.zeros(len(alist))
    for i in range(len(X)):
        X[i] = float(alist[i])
    return X

def main():

    counter = -1
    replay_X = []
    replay_Y = []

    performance_vars = read_old_performance_vars()
    n_performance_vars = len(performance_vars)
    control_vars = read_control_vars()
    n_control_vars = len(control_vars)
    #static_control_vars = np.ones(n_control_vars)
    n_actions = n_control_vars * 2 + 1 #the +1 is for "do nothing" action
    changes = np.zeros(n_control_vars)

    if(os.path.isfile('model.json')):
        json_file = open('model.json', 'r')
        loaded_model_json = json_file.read()
        json_file.close()
        model = model_from_json(loaded_model_json)
        # load weights into new model
        model.load_weights("model.h5")
        print("Loaded model from disk")
        # Read replay and counter from disk
        read_replay(replay_X,replay_Y)
    else:
        model = Sequential()
        model.add(Dense(25, input_dim=n_performance_vars, activation='relu'))
        model.add(Dense(50, kernel_initializer='random_normal',
                        bias_initializer='zeros', activation='relu'))
        model.add(Dense(100, kernel_initializer='random_normal',
                        bias_initializer='zeros',activation='relu'))
        model.add(Dense(100, kernel_initializer='random_normal',
                        bias_initializer='zeros',activation='relu'))
        model.add(Dense(n_actions, kernel_initializer='zeros',
                        bias_initializer='zeros',activation='relu'))
        model.add(Dense(n_actions, activation='linear'))
        
    adam = optimizers.Adam(lr=0.02, beta_1=0.9, beta_2=0.999, epsilon=1E-8, decay=0.001, amsgrad=False)
    
    model.compile(loss='mse', optimizer=adam, metrics=['accuracy'])

    epsilon = 0.1
    alpha = 0.5
    discount_factor = 1.0

    counter = read_counter()
    counter = counter + 1
    if(counter == 200):
       lb = random.randint(0, int(len(replay_X)/4))
       ub = random.randint(int(len(replay_X)/4), int(len(replay_X)/4)*3)
       print(lb,ub)
       model.fit(np.array(replay_X[lb:ub]),np.array(replay_Y[lb:ub]),verbose=0)
       counter = 0
    policy = make_epsilon_greedy_policy(model, epsilon, n_actions)
    np_performance_vars = fromDictToNp(performance_vars)
    print(np_performance_vars)
    state = np_performance_vars#np.floor(np_performance_vars)
    total_reward = 0
    action_probs = policy(np.array([state]))
    action = np.random.choice(np.arange(len(action_probs)), p=action_probs)
    if(int(action/2) >= n_control_vars):
        pass
    elif(action%2 == 0):
        changes[int(action/2)] = -1
    else:
        changes[int(action/2)] = 1
    new_perf_vars = fromDictToNp(read_performance_vars())
    reward = check_reward(performance_vars, np_performance_vars, new_perf_vars)
    np_performance_vars[:] = new_perf_vars[:]
    next_state = new_perf_vars#np.floor(new_perf_vars)
    next_action = select_next_action(model, np.array([next_state]))
    # Update policy
    total_reward += reward
    X = state
    X = np.array([X])
    Y = get_Q_value(X,action,model)
    Y_next = get_Q_value(np.array([next_state]),next_action,model)
    td_target = reward + discount_factor * float(Y_next)
    td_delta = td_target - float(Y)
    Y = np.array([float(Y) + alpha * td_delta])
    Y_all = get_Q_value_all_actions(X,model)
    Y_all[0][action] = Y
    replay_X.extend(X)
    replay_Y.extend(Y_all)
    write_replay(replay_X, replay_Y)
    model.fit(X,Y_all,verbose=0)
    write_counter(counter)
    write_changes(changes)
    model_json = model.to_json()
    with open("model.json", "w") as json_file:
        json_file.write(model_json)
    # serialize weights to HDF5
    model.save_weights("model.h5")
    print("Saved model to disk")

if __name__ == '__main__':
    main()
