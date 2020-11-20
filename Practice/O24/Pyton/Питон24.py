import json

users_list = []

input_data = open('in.json', 'r')
input_object = json.load(input_data)

output_data = open('out.json', 'w')


for tasks in input_object:
    user_dev = {}
    if tasks['completed'] == True:
        check_working = True
        count = 0
        user_dev['task_completed'] = 0
        user_dev['userId'] = 0
        for user_id in users_list:
            if user_id['userId'] == tasks['userId']:
                check_working = False
                users_list[count]['task_completed'] += 1
                break
            count += 1
        if check_working == True:
            user_dev['userId'] = tasks['userId']
            user_dev['task_completed'] += 1
            users_list.append(user_dev)

output_data.write(json.dumps(users_list, indent=3))class my_class(object):
    pass




