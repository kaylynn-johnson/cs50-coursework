// JS related to the unique items of the profile page

document.addEventListener('DOMContentLoaded', function() {

    try {
        // Determine Follow status
        const receiver_user = document.querySelector('#follow').dataset.userId;
        determine_follow_status(receiver_user);

        document.querySelector('#follow').addEventListener('click', button => {
            // trigger post request
            change_follow_status(receiver_user);
        });
    }
    catch(error) {
        console.log(error);
    }
});

// Fetch CSRF Token from meta tag in header
function getCsrfToken() {
    const metaTag = document.querySelector('meta[name="csrf-token"]');
    if (metaTag) {
        // Successfully found tag
        return metaTag.content;
    }
    throw new Error('CSRF token meta tag not found');
}

// Determine follow status with GET request
function determine_follow_status(username) {
    fetch(`/profile/${username}/follow`)
    .then(response => response.json())
    .then(request => {
        if (request.error !== undefined) {
            alert(request.error);
        } else {
            if (request.follower) {
                document.querySelector('#follow').innerHTML = "Unfollow";
            } else {
                document.querySelector('#follow').innerHTML = "Follow";
            }
        }
    });
}

// Change follow status with POST request
function change_follow_status(username) {
    // determine if currently following or not
    const follow_status = document.querySelector('#follow').innerHTML
    let follow;
    if (follow_status === "Unfollow") {
        follow = false;
    } else {
        follow = true;
    }

    fetch(`/profile/${username}/follow`, {
        method: 'POST',
        headers: {
            'X-CSRFToken': getCsrfToken()
        },
        body: JSON.stringify({
            follow: follow
        })
    })
    .then(response => response.json())
    .then(request => {
        if (request.error !== undefined) {
            alert(request.error);
        } else {
            // change follower count
            const follower_count = document.querySelector('#follower-count').innerHTML;
            if (follow) {
                // Add to follower count & flip follow wording
                document.querySelector('#follower-count').innerHTML = parseInt(follower_count) + 1;
                document.querySelector('#follow').innerHTML = "Unfollow";
            } else {
                // Remove from follower count
                document.querySelector('#follower-count').innerHTML = parseInt(follower_count) - 1;
                document.querySelector('#follow').innerHTML = "Follow";
            }
        }
    });
}