document.addEventListener('DOMContentLoaded', function() {

  // Use buttons to toggle between views
  document.querySelector('#inbox').addEventListener('click', () => load_mailbox('inbox'));
  document.querySelector('#sent').addEventListener('click', () => load_mailbox('sent'));
  document.querySelector('#archived').addEventListener('click', () => load_mailbox('archive'));
  document.querySelector('#compose').addEventListener('click', () => compose_email('empty'));
  document.querySelector('#send-email').addEventListener('click', send_email);

  // By default, load the inbox
  load_mailbox('inbox');
});

function compose_email(email) {

  // Show compose view and hide other views
  document.querySelector('#emails-view').style.display = 'none';
  document.querySelector('#email-section').style.display = 'none';
  document.querySelector('#compose-view').style.display = 'block';

  if (email === 'empty') {
    // Clear out composition fields
    document.querySelector('#compose-recipients').value = '';
    document.querySelector('#compose-subject').value = '';
    document.querySelector('#compose-body').value = '';
  } else {
    // Reply button was passed so pre-fill fields
    document.querySelector('#compose-recipients').value = email.sender;
    if (email.subject.includes('Re: ')) {
      // Don't need to add the Re prefix
      document.querySelector('#compose-subject').value = email.subject;
    } else {
      // Add Re prefix
      document.querySelector('#compose-subject').value = `Re: ${email.subject}`;
    }
    document.querySelector('#compose-body').value = `\r\n\r\nOn ${email.timestamp} ${email.sender} wrote: \r\n${email.body}`
  }
  
}

function send_email() {
  console.log('Send email');

  recipients = document.querySelector('#compose-recipients').value;
  subject = document.querySelector('#compose-subject').value;
  body = document.querySelector('#compose-body').value;

  console.log(`Sending email to ${recipients} about ${subject}`);

  fetch('/emails', {
    method: 'POST',
    body: JSON.stringify({
      recipients: recipients,
      subject: subject,
      body: body
    })
  })
  .then(response => response.json())
  .then(result => {
    if (result.error !== undefined) {
      // give alert
      alert(`Error: ${result.error}`);
      console.log(`${result.error}`);
      load_mailbox('inbox');
    } else {
      console.log(result);
      load_mailbox('sent');
    }
    // console.log(result.error);
    // console.log(result);
    // load_mailbox('sent');
  });

  
}

function load_mailbox(mailbox) {
  
  // Show the mailbox and hide other views
  document.querySelector('#emails-view').style.display = 'block';
  document.querySelector('#compose-view').style.display = 'none';
  document.querySelector('#email-section').style.display = 'none';

  // Show the mailbox name
  document.querySelector('#emails-view').innerHTML = `<h3>${mailbox.charAt(0).toUpperCase() + mailbox.slice(1)}</h3>`;

  // Fetch emails for mailbox
  fetch(`/emails/${mailbox}`)
  .then(response => response.json())
  .then(emails => {
    console.log(emails);

    // Create DOM elements to display the emails
    emails.forEach(email => {
      const element = document.createElement('div');


      const sender = document.createElement('div');
      sender.innerHTML = email.sender;
      sender.style.fontWeight = 800;
      element.append(sender);

      const subject = document.createElement('div');
      subject.innerHTML = email.subject;
      element.append(subject);

      const timestamp = document.createElement('div');
      timestamp.innerHTML = email.timestamp;
      timestamp.style.textAlign = 'end';
      timestamp.style.color = 'gray';
      element.append(timestamp);

      element.style.display = 'grid';
      element.style.setProperty('grid-template-columns', '200px auto auto');
      element.style.border = 'solid 1px';

      // change background depending on if it has been read or not
      if (email.read) {
        element.style.backgroundColor = 'white';
      } else {
        element.style.backgroundColor = '#B0B0B0';
      }
      element.id = email.id;

      // Add event listener
      element.addEventListener('click', () => view_email(email.id, mailbox));
      document.querySelector('#emails-view').append(element);
    });
  });
}

function view_email(id, mailbox) {

  // Show the mailbox and hide other views
  document.querySelector('#emails-view').style.display = 'none';
  document.querySelector('#compose-view').style.display = 'none';
  document.querySelector('#email-section').style.display = 'block';

  // Get email details
  fetch(`/emails/${parseInt(id)}`)
  .then(response => response.json())
  .then(email => {
    // Print out email information
    // Empty current email-section
    const email_section = document.querySelector('#email-section')
    email_section.innerHTML = '';
    
    // Archive button
    if (mailbox !== 'sent') {
      const archive = document.createElement('button');
      if (mailbox === 'inbox') {
        archive.innerHTML = 'Archive';
        // Add event listener
        archive.addEventListener('click', () => archive_email(email.id, true));
      } else {
        archive.innerHTML = 'Unarchive';
        // Add event listener
        archive.addEventListener('click', () => archive_email(email.id, false));
      }
      archive.classList.add('btn', 'btn-sm', 'btn-outline-primary');
      
      email_section.append(archive);
    }

    // Sender line
    const sender = document.createElement('div');
    sender.innerHTML = `<b>From:</b> ${email.sender}`;
    email_section.append(sender);

    // To line
    const recipient = document.createElement('div');
    recipient.innerHTML = `<b>To:</b> ${email.recipients}`;
    email_section.append(recipient);

    // Subject line
    const subject = document.createElement('div');
    subject.innerHTML = `<b>Subject:</b> ${email.subject}`;
    email_section.append(subject);

    // Timestamp
    const timestamp = document.createElement('div');
    timestamp.innerHTML = `<b>Timestamp:</b> ${email.timestamp}`;
    email_section.append(timestamp);

    // Reply button
    const reply = document.createElement('button');
    reply.innerHTML = 'Reply';
    // Add event listener
    reply.addEventListener('click', () => compose_email(email));
    reply.classList.add('btn', 'btn-sm', 'btn-outline-primary');
    email_section.append(reply);

    // Email body
    const body = document.createElement('div');
    body.innerHTML = email.body;
    body.style.marginTop = '20px';
    body.style.whiteSpace = 'pre-wrap';
    email_section.append(body);
    
  });

  // Mark email as read
  fetch(`/emails/${parseInt(id)}`, {
    method: 'PUT',
    body: JSON.stringify({
      read: true
    })
  });
}

function archive_email(id, action) {
  fetch(`/emails/${parseInt(id)}`, {
    method: 'PUT',
    body: JSON.stringify({
      archived: action
    })
  })
  .then(response => load_mailbox('inbox'));
}