from smtplib import SMTP_SSL
from smtplib import SMTP
from imaplib import IMAP4_SSL
MAILBOX = 'kuzmichevdima95'
PASSWD = 'hao54jh5qa897lt'
who = '%s@gmail.com' % MAILBOX
from_ = who
to = [who]
headers = [
    'From: %s' % from_,
    'To: %s' % ', '.join(to),
    'Subject: test SMTP send',
]
body = [
    'Hello',
    'World!',
]
print(who)
#msg = '\r\n\r\n'.join(('\r\n'.join(headers), '\r\n'.join(body)))
s = SMTP('smtp.gmail.com', 587)
s.starttls()
s.login(MAILBOX, PASSWD)
#s.sendmail(from_, to, msg)
#s.quit()
#s = IMAP4_SSL('imap.gmail.com', 993)
#s.login(MAILBOX, PASSWD)
