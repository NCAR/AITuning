import MPICH_DQN_parabola_Q_learning as MPICH

def test_read_performance_vars():
    stuff = MPICH._read_performance_vars(
"""
unexpected_recvq_length_avg=1.46711
unexpected_recvq_length_max=7
num_procs_avg=8
num_procs_max=8
total_time_avg=0.03125
total_time_max=0.03125
put_time_avg=0
put_time_max=0
get_time_avg=0
get_time_max=0
flush_time_avg=0
flush_time_max=0
""")
    assert stuff['unexpected_recvq_length_avg'] == 1.46711
    assert stuff['flush_time_avg'] == 0
    assert stuff['total_time_max'] == 0.03125

def test_read_control_vars():
    stuff = MPICH._read_control_vars(
"""
MPIR_CVAR_ASYNC_PROGRESS=0
MPIR_CVAR_CH3_ENABLE_HCOLL=0
MPIR_CVAR_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING=0
MPIR_CVAR_CH3_RMA_OP_PIGGYBACK_LOCK_DATA_SIZE=65536
MPIR_CVAR_POLLS_BEFORE_YIELD=1000
"""
)
    assert stuff[0] == 1.61988
    assert stuff[-1] == 0
    assert stuff[-2] == 12
