from ctf_helper import *

id_token = "eyJhbGciOiJFZERTQSIsImtpZCI6ImlkIiwidHlwIjoiSldUIn0.eyJzdWIiOiJOaWtvbGFpLkdhbmdzdG8iLCJpc3MiOiJodHRwczovL2luZjIyNi5wdWZmbGluZy5ubyIsImlhdCI6MTc1ODgwMjUzMSwic2NvcGUiOlsiaWQiXX0.05RnSNXWEuHiFIOWcUefRfkTm7ll-I3dCTbUCweXQ1FESBTV1H-xquaPnY8vND1rcdEf9BE6ViGh5w5vq_TyBA"  # insert your token here

io : tube = start(7000)

read_welcome(id_token)


next_qa()

### May help you decode the final success/fail response
log_answer(read_answer())
