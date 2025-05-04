import sys
import smtplib
from email.mime.text import MIMEText
print("Arguments reçus :", sys.argv)

# Récupération des arguments
if len(sys.argv) < 4:
    print("Usage: send_email.py email sujet message")
    sys.exit(1)

destinataire = sys.argv[1]
sujet = sys.argv[2]
message = sys.argv[3]
print(f"Envoi de l'email à : {destinataire}")

# Informations de l'expéditeur
email_expediteur = "nawreskhalifa12@gmail.com"
mot_de_passe = "xsgk uxcv vtjd csmn"

# Construction du message
msg = MIMEText(message)
msg["Subject"] = sujet
msg["From"] = email_expediteur
msg["To"] = destinataire

try:
    print("Connexion à smtp.gmail.com sur le port 465...")
    with smtplib.SMTP_SSL("smtp.gmail.com", 465) as server:
        print("Tentative de login...")
        server.login(email_expediteur, mot_de_passe)
        print("Login réussi, envoi du message...")
        print("Envoi du mail à (dans le script Python) :", destinataire)
        print("Contenu final du message :", msg.as_string())
        server.send_message(msg)
    print("Email envoyé avec succès")
except Exception as e:
    print("Erreur lors de l'envoi :", e, file=sys.stderr)
    sys.exit(1)