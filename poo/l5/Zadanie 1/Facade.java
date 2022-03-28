import javax.mail.*;
import javax.mail.internet.*;
import java.io.File;
import java.io.IOException;
import java.util.Properties;
import java.util.Scanner;

public class Facade {
    static class SmtpFacade {
        public void send(String from, String to,
                         String subject, String body, File attachment) throws MessagingException, IOException {
            Properties prop = new Properties();
            prop.put("mail.smtp.auth", true);
            prop.put("mail.smtp.starttls.enable", "true");
            prop.put("mail.smtp.host", "smtp.mailtrap.io");
            prop.put("mail.smtp.port", "25");
            prop.put("mail.smtp.ssl.trust", "smtp.mailtrap.io");
            Session session = Session.getInstance(prop, new Authenticator() {
                @Override
                protected PasswordAuthentication getPasswordAuthentication() {
                    Scanner scanner = new Scanner(System.in);
                    System.out.println("Nazwa użytkownika:");
                    String userName = scanner.nextLine();
                    System.out.println("Hasło:");
                    String password = scanner.nextLine();
                    return new PasswordAuthentication(userName, password);
                }
            });

            Message message = new MimeMessage(session);
            message.setFrom(new InternetAddress(from));
            message.setRecipient(Message.RecipientType.TO, new InternetAddress(to));
            message.setSubject(subject);

            MimeBodyPart mimeBodyPart = new MimeBodyPart();
            mimeBodyPart.setContent(body, "text/html");

            MimeBodyPart attachmentBodyPart = new MimeBodyPart();
            attachmentBodyPart.attachFile(attachment);

            Multipart multipart = new MimeMultipart();
            multipart.addBodyPart(mimeBodyPart);
            multipart.addBodyPart(attachmentBodyPart);

            message.setContent(multipart);
            Transport.send(message);
        }
    }

    public static void main(String[] args) {
        try {
            SmtpFacade smtpFacade = new SmtpFacade();
            smtpFacade.send("nadawca@gmail", "odbiorca@gmail.pl",
                    "temat", "tresc", new File("zalacznik.txt"));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
