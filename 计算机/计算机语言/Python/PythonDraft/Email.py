import smtplib
from email.mime.text import MIMEText
from email.utils import formataddr

# ### 1.邮件内容配置 ###
# 邮件文本
msg = MIMEText("python测试", 'html', 'utf-8')
# 邮件上现实的发件人
msg['From'] = formataddr(["阿飞", "liuyifei97@163.com"])
# 邮件上显示的主题
msg['Subject'] = "python email sending test"

# ### 2.发送邮件 ###
server = smtplib.SMTP_SSL("smtp.163.com")
server.login("liuyifei97@163.com", "NHEIWFACDZFBKWAD")
server.sendmail("liuyifei97@163.com", "f384656162@163.com", msg.as_string())
server.quit()
