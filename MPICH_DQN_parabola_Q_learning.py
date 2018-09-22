import numpy as np
from collections import defaultdict
from math import floor
import random
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Conv1D
from keras.layers import advanced_activations
from keras import optimizers

n_control_vars = 6
n_performance_vars = 12
n_steps = 1
n_episodes = 1000
n_actions = n_control_vars * 2 + 1

perf_var_names = [
"unexpected_recvq_length_avg",
"unexpected_recvq_length_max",
"num_rpocs_avg",
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
    for i in changes:
        file_object.write(str(changes[i])+" ")

def read_control_vars():
    return _read_control_vars(open('control_variables.txt', 'r').read())

def read_performance_vars():
    return _read_performance_vars(open('performance_variables.txt', 'r').read())

def simulate_execution(control_vars, performance_vars):
    global n_performance_vars
    global n_control_vars
    global static_control_vars
    
    randomness = np.random.rand(1)
    new_perf_vars = np.zeros(n_performance_vars)
    new_perf_vars[:] = performance_vars[:]

    new_perf_vars[n_performance_vars - 1] = (control_vars[n_control_vars - 1] - 200.) ** 2 + randomness
    new_perf_vars[n_performance_vars - 2] = (control_vars[n_control_vars - 2] - 20.) ** 2 + randomness
    new_perf_vars[n_performance_vars - 3] = (control_vars[n_control_vars - 3] - 15.) ** 2 + randomness
    new_perf_vars[n_performance_vars - 4] = (control_vars[n_control_vars - 4] - 156.) ** 2 + randomness
    
    return np.floor(new_perf_vars)

def check_reward(performance_vars, new_perf_vars):
    reward = 0
    for i in range(n_performance_vars):
        if(performance_vars[i] > new_perf_vars[i]):
            reward = reward + 20
        elif(performance_vars[i] < new_perf_vars[i]):
            reward = reward - 50
        if(performance_vars[i] == new_perf_vars[i]):
            reward = reward - 1
    return reward

def make_epsilon_greedy_policy(Q,epsilon,n_actions):
    
    def policy_fn(state):
        A = np.ones(n_actions, dtype=float) * epsilon / (n_actions)
        Y = model.predict(state)
        best_action = np.argmax(Y)
        A[best_action] += (1.0 - epsilon)
        return A
    return policy_fn

def select_next_action(next_state):
    Y = model.predict(next_state)
    best_action = np.argmax(Y)
    return best_action

def get_Q_value(X,action):
    Y = model.predict(X)
    return Y[0][action]

def get_Q_value_all_actions(X):
    Y = model.predict(X)
    return Y

def main():
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
    
    static_control_vars = np.ones(n_control_vars)
    
    epsilon = 0.1
    alpha = 0.5
    discount_factor = 1.0
    
    Q = defaultdict(lambda: np.ones(n_actions))
    
    control_vars = np.ones(n_control_vars)
    performance_vars = np.ones(n_performance_vars)
    action_frequency = np.zeros(n_actions)
    counter = -1
    replay_X = []
    replay_Y = []
    
    for i in range(n_episodes):
        counter = counter + 1
        if(counter == 200):
            lb = random.randint(0, int(len(replay_X)/4))
            ub = random.randint(int(len(replay_X)/4), int(len(replay_X)/4)*3)
            print(lb,ub)
            model.fit(np.array(replay_X[lb:ub]),np.array(replay_Y[lb:ub]),verbose=0)
            counter = -1
        policy = make_epsilon_greedy_policy(Q,epsilon,n_actions)
        state = np.floor(performance_vars)
        total_reward = 0
        for j in range(n_steps):
            action_probs = policy(np.array([state]))
            action = np.random.choice(np.arange(len(action_probs)), p=action_probs)
            if(int(action/2) >= n_control_vars):
                pass
            elif(action%2 == 0):
                control_vars[int(action/2)] = control_vars[int(action/2)] - 1
            else:
                control_vars[int(action/2)] = control_vars[int(action/2)] + 1
            # new_perf_vars = simulate_execution(control_vars, performance_vars)
            new_perf_vars = read_performance_vars()
            reward = check_reward(performance_vars, new_perf_vars)
            performance_vars[:] = new_perf_vars[:]
            next_state = np.floor(new_perf_vars)
            next_action = select_next_action(np.array([next_state]))
            # Update policy
            total_reward += reward
            X = state
            X = np.array([X])
            Y = get_Q_value(X,action)
            Y_next = get_Q_value(np.array([next_state]),next_action)
            td_target = reward + discount_factor * float(Y_next)
            td_delta = td_target - float(Y)
            Y = np.array([float(Y) + alpha * td_delta])
            Y_all = get_Q_value_all_actions(X)
            Y_all[0][action] = Y
            replay_X.extend(X)
            replay_Y.extend(Y_all)
            model.fit(X,Y_all,verbose=0)
            state[:] = next_state[:]
            action_frequency[action] += 1
            
        print("total reward",total_reward)#,"action frequency",action_frequency)

if __name__ == '__main__':
    main()
