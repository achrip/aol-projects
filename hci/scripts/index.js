// poster slideshow
let slideIndex = [1, 1, 1, 1]; 
let slideId = ["slides0", "slides1", "slides2", "slides3"]; 
showSlides(1, 0); 
showSlides(1, 1); 
showSlides(1, 2); 
showSlides(1, 3); 

function plusSlides(n, no) {
    showSlides(slideIndex[no] += n, no); 
}

function showSlides (n, no) {
    let i; 
    let x = document.getElementsByClassName(slideId[no]); 
    if (n > x.length) {slideIndex[no] = 1}
    if (n < 1) {slideIndex[no] = x.length} 
    for (i = 0; i < x.length; i++) {
        x[i].style.display = "none"; 
    }
    x[slideIndex[no]-1].style.display = "block"; 
}

const slide0next = document.getElementById("next0"); 
const slide1next = document.getElementById("next1"); 
const slide2next = document.getElementById("next2"); 
const slide3next = document.getElementById("next3"); 
const slide0prev = document.getElementById("prev0"); 
const slide1prev = document.getElementById("prev1"); 
const slide2prev = document.getElementById("prev2"); 
const slide3prev = document.getElementById("prev3"); 


slide0next.onclick = function() {plusSlides(1,0)}; 
slide1next.onclick = function() {plusSlides(1,1)}; 
slide2next.onclick = function() {plusSlides(1,2)}; 
slide3next.onclick = function() {plusSlides(1,3)}; 
slide0prev.onclick = function() {plusSlides(-1,0)}; 
slide1prev.onclick = function() {plusSlides(-1,1)}; 
slide2prev.onclick = function() {plusSlides(-1,2)}; 
slide3prev.onclick = function() {plusSlides(-1,3)}; 