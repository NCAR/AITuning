import MPICH_DQN_parabola_Q_learning as MPICH

def test_read_performance_vars():
    stuff = MPICH._read_performance_vars("1.61988 7.375 8 8 0.305 0.305 0 0 0 0 0 0")
    assert stuff[0] == 1.61988
    assert stuff[-1] == 0
    assert stuff[-2] == 12
