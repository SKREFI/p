from twilio.rest import Client
import os
from time import sleep

os.environ['TWILIO_ACCOUNT_SID'] = 'ACbad59847ce4f44efe66740bc8bad35dc'
os.environ['TWILIO_AUTH_TOKEN'] = '600c18b9d1eaf775c1fa4f87cbd4f56b'

# old
# message = ''

# index = 4
# for p in phones:
#     message += 'Nr. ' + str(index) + '\n' + \
#         'https://api.whatsapp.com/send?phone=' + p + '\n'

# c.messages.create(body=message, from_=from_number, to=to_number)


c = Client(account_sid='ACbad59847ce4f44efe66740bc8bad35dc')

from_number = 'whatsapp:+14155238886'
to_number = 'whatsapp:+40773993932'

phones = [
    '0755341083',
    '0733805688',
    '0731446390',
    '0733884983',
    '0770278374',
    '0763799026',
    '0765925277',
    '0751294658',
    '0752610537',
    '0762404507',
    '0725434340',
    '0731563671',
    '0731266116'
]

for i in range(len(phones)):
    if phones[i][0] == '+':
        phones[i] = phones[i][1:]
    if phones[i][0] == '7':
        phones[i] = '40' + phones[i]
    if phones[i][0] == '0':
        phones[i] = '4' + phones[i]


index = 18
for p in phones:
    c.messages.create(body='Nr. ' + str(index) + '\n' +
                      'https://api.whatsapp.com/send?phone=' + p + '\n', from_=from_number, to=to_number)
    print('Sent link for: ', p)
    sleep(1)
    index += 1
