import numpy as np
from collections import defaultdict
from math import floor
import random, argparse

def simulate_execution(control_vars, performance_vars, target, noise_level):
    new_perf_vars = np.zeros(len(performance_vars))
    new_perf_vars[:] = performance_vars[:]

    for i in range(len(performance_vars)):
        randomness = np.random.rand(1) * target[i] * noise_level / 100
        new_perf_vars[i] = (control_vars[i] - target[i]) ** 2 + randomness

    return np.floor(new_perf_vars)

def check_reward(performance_vars, new_perf_vars):
    reward = 0
    for i in range(len(performance_vars)):
        if(performance_vars[i] > new_perf_vars[i]):
            reward = reward + 20
        elif(performance_vars[i] < new_perf_vars[i]):
            reward = reward - 50
        if(performance_vars[i] == new_perf_vars[i]):
            reward = reward - 1
    return reward

def make_epsilon_greedy_policy(Q,epsilon,n_actions,model):
    def policy_fn(state):
        A = np.ones(n_actions, dtype=float) * epsilon / (n_actions)
        Y = model.predict(state)
        best_action = np.argmax(Y)
        A[best_action] += (1.0 - epsilon)
        return A
    return policy_fn

def select_next_action(next_state, model):
    Y = model.predict(next_state)
    best_action = np.argmax(Y)
    return best_action

def get_Q_value(X,action, model):
    Y = model.predict(X)
    return Y[0][action]

def get_Q_value_all_actions(X, model):
    Y = model.predict(X)
    return Y

def run(args):
    n_control_vars = 4
    n_performance_vars = 4
    target = [200, 20, -3, -150]
    print("Target values:", target)
    n_steps = 1
    n_actions = n_control_vars * 2 + 1

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

    Q = defaultdict(lambda: np.ones(n_actions))

    control_vars = np.ones(n_control_vars)
    performance_vars = np.ones(n_performance_vars)
    action_frequency = np.zeros(n_actions)
    counter = -1
    replay_X = []
    replay_Y = []

    for i in range(args.episodes):
        counter = counter + 1
        if(counter == 200):
            lb = random.randint(0, int(len(replay_X)/4))
            ub = random.randint(int(len(replay_X)/4), int(len(replay_X)/4)*3)
            #print(lb,ub)
            model.fit(np.array(replay_X[lb:ub]),np.array(replay_Y[lb:ub]),verbose=0)
            counter = -1
        policy = make_epsilon_greedy_policy(Q,epsilon,n_actions, model)
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
            new_perf_vars = simulate_execution(control_vars, performance_vars, target, args.noise_level)
            reward = check_reward(performance_vars, new_perf_vars)
            performance_vars[:] = new_perf_vars[:]
            next_state = np.floor(new_perf_vars)
            next_action = select_next_action(np.array([next_state]), model)
            # Update policy
            total_reward += reward
            X = state
            X = np.array([X])
            Y = get_Q_value(X,action, model)
            Y_next = get_Q_value(np.array([next_state]),next_action, model)
            td_target = reward + discount_factor * float(Y_next)
            td_delta = td_target - float(Y)
            Y = np.array([float(Y) + alpha * td_delta])
            Y_all = get_Q_value_all_actions(X, model)
            Y_all[0][action] = Y
            replay_X.extend(X)
            replay_Y.extend(Y_all)
            model.fit(X,Y_all,verbose=0)
            state[:] = next_state[:]
            action_frequency[action] += 1

        if (i % args.print_frequency == 0) and not (args.quiet):
        #print("action frequency",action_frequency)
            print("Episode: ", i, "/", args.episodes, "-- Total reward: ",total_reward, "-- Control variables",control_vars)
    abs_error = target - control_vars
    rel_error = 1 - control_vars / target

    if not (args.quiet):
        print("Episode: ", args.episodes, "/", args.episodes, "-- Total reward: ",total_reward, "-- Control variables",control_vars)
        print("Accuracies: ", abs_error)
        print("Accuracies: ", 100*rel_error, "%")
    return abs_error, rel_error

def print_errors(err, prefix):
    print(prefix, err)
    print("---")
    print(prefix, "(median): ", np.median(err, axis=0))
    print(prefix, "(mean):   ", np.mean  (err, axis=0))
    print(prefix, "(stddev): ", np.std   (err, axis=0))
    print(prefix, "(max):    ", np.amax  (err, axis=0))
    print(prefix, "(min):    ", np.amin  (err, axis=0))
    print("---")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--print-frequency', type=int, default=500, help='Print summary every PRINT_FREQUENCY episodes')
    parser.add_argument('-e', '--episodes', type=int, default=5000, help='Number of EPISODES to run')
    parser.add_argument('-n', '--noise_level', type=int, default=5, help='Noise in the performance measurements (%%)')
    parser.add_argument('-l', '--loop', type=int, default=1, help='Repeat LOOP times and average results')
    parser.add_argument('-q', '--quiet', action='store_true', help='Do not print details on the episodes')
    args = parser.parse_args()
    print("Configuration", args)

    from keras.models import Sequential
    from keras.layers import Dense
    from keras.layers import Conv1D
    from keras.layers import advanced_activations
    from keras import optimizers

    abs_errors = []
    rel_errors = []
    loop = args.loop
    del args.loop
    for i in range(loop):
        print("Running iteration", i+1, "of", loop)
        abs_err, rel_err = run(args)
        abs_errors.append(abs_err)
        rel_errors.append(rel_err)
    print_errors(abs_errors, "Absolute accuracy")
    print_errors(rel_errors, "Relative accuracy")
