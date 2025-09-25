from ctf_helper import *

id_token = ""  # insert your token here

io : tube = start(7000)

read_welcome()

### REPLACE WITH YOUR CODE
io.sendline(b'something')

next_qa()

### May help you decode the final success/fail response
log_answer(read_answer())
