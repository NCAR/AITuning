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
    assert stuff['MPIR_CVAR_ASYNC_PROGRESS'] == 0
    assert stuff['MPIR_CVAR_CH3_RMA_DELAY_ISSUING_FOR_PIGGYBACKING'] == 0
    assert stuff['MPIR_CVAR_POLLS_BEFORE_YIELD'] == 1000

replay_data = """
X [[1.52226e+01 6.90000e+01 7.00000e+01 7.00000e+01 5.97114e+00 5.97114e+00
  0.00000e+00 0.00000e+00 0.00000e+00 0.00000e+00 1.08714e-02 1.08714e-02]]

X [[ 1.52226e+01  6.90000e+01  7.00000e+01  7.00000e+01 -1.24857e-01
  -1.24857e-01  0.00000e+00  0.00000e+00  0.00000e+00  0.00000e+00
   1.08714e-02  1.08714e-02]]

X [[ 1.52172e+01  6.90000e+01  7.00000e+01  7.00000e+01 -6.34857e-01
  -6.34857e-01  0.00000e+00  0.00000e+00  0.00000e+00  0.00000e+00
   1.08714e-02  1.08714e-02]]

X [[ 1.52255e+01  6.90000e+01  7.00000e+01  7.00000e+01 -9.97143e-02
  -9.97143e-02  0.00000e+00  0.00000e+00  0.00000e+00  0.00000e+00
   1.10571e-02  1.17286e-02]]

X [[ 1.52203e+01  6.90000e+01  7.00000e+01  7.00000e+01 -4.49714e-01
  -4.49714e-01  0.00000e+00  0.00000e+00  0.00000e+00  0.00000e+00
   1.08714e-02  1.08714e-02]]

X [[ 1.52535e+01  6.92714e+01  7.00000e+01  7.00000e+01 -2.48571e-02
  -2.48571e-02  0.00000e+00  0.00000e+00  0.00000e+00  0.00000e+00
   1.09943e-02  1.14714e-02]]

Y [[-4.0005408e-02 -5.9999987e-02 -5.9999604e-02 -7.9999924e-02
  -5.9999973e-02 -5.9999980e-02 -4.0000156e-02 -5.9999995e-02
  -4.0000111e-02 -1.2289440e+02 -5.9999943e-02 -5.9999865e-02
  -1.1999987e-01]]

Y [[-4.0005408e-02 -5.9999987e-02 -5.9999604e-02 -7.9999924e-02
  -5.9999973e-02 -5.9999980e-02 -4.0000156e-02 -5.9999995e-02
   7.4159966e+01 -7.9999998e-02 -5.9999943e-02 -5.9999865e-02
  -1.1999987e-01]]

Y [[-0.04000541 -0.05999999 -0.0599996  -0.07999992 -0.05999997 -0.05999998
  -0.04000016 -0.05999999  6.355      -0.08       -0.05999994 -0.05999986
  -0.11999987]]

Y [[ -0.04000541  -0.05999999  -0.0599996   -0.07999992  -0.05999997
   -0.05999998  -0.04000016  -0.05999999 -17.329855    -0.08
   -0.05999994  -0.05999986  -0.11999987]]

Y [[-0.04000541 -0.05999999 -0.0599996  -0.07999992 -0.05999997 -0.05999998
  -0.04000016 -0.05999999  8.354996   -0.08       -0.05999994 -0.05999986
  -0.11999987]]

Y [[ -0.04000541  -0.05999999  -0.0599996   -0.07999992  -0.05999997
   -0.05999998  -0.04000016  -0.05999999 -16.01014     -0.08
   -0.05999994  -0.05999986  -0.11999987]]A
"""

def test_replay():
    print("use the previous data to implement a replay test")
    assert False, "To be implemented"
