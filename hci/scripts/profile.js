const form = document.getElementById('reg-form'); 

const uname = document.getElementById('uname'); 
const mail = document.getElementById('email'); 
const pwd = document.getElementById('password'); 
const rpwd = document.getElementById('repassword'); 
const tnc = document.getElementById('tnc'); 
const err = document.getElementById('err'); 

console.log('uname: ' + uname.value); 

form.addEventListener('submit', function (e) {
    e.preventDefault(); 

    err.innerHTML = ''; 
    if (uname.value.length < 5) {
        err.innerHTML += '<li class="err-msg">Username length too short</li>'; 
    }

    if (pwd.value != rpwd.value) {
        err.innerHTML += '<li class="err-msg">Passwords do not match</li>';
    }

    if (tnc.checked == false) {
        err.innerHTML += '<li class="err-msg">You must agree with the Terms and Conditions</li>'; 
    }

    if (mail.value == '') {
        err.innerHTML += '<li class="err-msg">Email cannot be empty</li>'; 
    }
    else {
        let substrs = mail.value.split('@'); 
        if (substrs.length > 2) {
            err.innerHTML += '<li class="err-msg">Bad email format</li>';  
        }
    
        checkEmail(mail.value)
    }
})

function checkEmail(email) {
    var atIndex = email.indexOf('@'); 
    var substrs = email.split('@'); 
    if (substrs.length > 2) {
        return false; 
    }

    var name = substrs[0]; 
    var domain = substrs[1];
    checkBadChar(name); 
    checkBadChar(domain); 
}

function checkBadChar(str) {
    var badChar = ['!', '#', '$', '%', '^', '&', '*', '(', ')', '-', '/', '~', '[', ']', '.', ',']; 

    if (badChar.includes(str[0])) {
        err.innerHTML += '<li class="err-msg">Bad email start</li>'; 
        return false; 
    }

    if (badChar.includes(str[str.length-1])) {
        err.innerHTML += '<li class="err-msg">Bad email end</li>'; 
        return false; 
    }

    return true; 
}

