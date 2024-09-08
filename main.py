import random

# s = 1
# x = -1
# p = 0

Bot = random.choice([1, -1, 0])

you_str = input("s: stone\np: paper\nx: scissor\nenter your choice; ").lower()
convertor_dict = {'s': 1, 'x': -1, 'p': 0}
you = convertor_dict[you_str]

Bot_dict = {1: "stone", -1: "scissor", 0: "paper"}
user_dict = {'s': "stone", 'x': "scissor", 'p': "paper"}

print('your choice:',user_dict[you_str])
print('Bot choice:',Bot_dict[Bot])

if(Bot == you):
    print("Draw")
else:
    if(you == 1 and Bot == -1):
        print("you win!")
    elif(you == 1 and Bot == 0):
        print('you lose!')
    elif(you == -1 and Bot == 1):
        print('you lose!')
    elif(you == -1 and Bot == 0):
        print('you win!')
    elif(you == 0 and Bot == 1):
        print('you win!')
    elif(you == 0 and Bot == -1):
        print('you lose!')
    else:
        print("something went wrong!")