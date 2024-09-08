# s = 1
# x = -1
# p = 0


import random
Bot = random.choice([1, -1, 0])

you_str = input("s: stone\np: paper\nx: scissor\nenter your choice; ").lower()
convertor_dict = {'s': 1, 'x': -1, 'p': 0}
you = convertor_dict[you_str]


dict = {1: "stone", -1: "scissor", 0: "paper"}

print('your choice:',dict[you])
print('Bot choice:',dict[Bot])


if(Bot == you):
    print("Draw")
else:
    if((you - Bot) == 1 or (you - Bot) == -2):
        print("you lose!")
    else:
        print("you win!")

#     if(you == 1 and Bot == -1): 2
#         print("you win!")
#     elif(you == 1 and Bot == 0): 1
#         print('you lose!')
#     elif(you == -1 and Bot == 1): -2
#         print('you lose!')
#     elif(you == -1 and Bot == 0): -1
#         print('you win!')
#     elif(you == 0 and Bot == 1): -1
#         print('you win!')
#     elif(you == 0 and Bot == -1): 1
#         print('you lose!')
#     else:
#         print("something went wrong!")