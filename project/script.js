
// });
// 1=>loader h1
// 2=>yellow1
// 3=>yellow2
// 4=>loader video
var check = true
var plus = document.querySelector("#plus")
console.log(plus)

plus.addEventListener("click",()=>{
  var tl2 = gsap.timeline();
  if(check){

    tl2.to("#three",{
      opacity:0,
      x:"150%"
     },"anime")
     tl2.to("#two",{
      x:"320%",
      opacity:0,
     },"anime")
     tl2.to("#one",{
      // opacity:0,
      duration:0.5,
      x:"300%"
     },"anime")
   check= false
  }
  else{

    tl2.to("#one",{
      // opacity:0,
      duration:0.5,
      x:"0"
     },"anime2")
     tl2.to("#two",{
      x:"0",
      opacity:1,
     },"anime2")
    tl2.to("#three",{
      opacity:1,
      x:"0"
     },"anime2")

     check= true
  }
   
  
})
function loading(){

  var tl = gsap.timeline();

  gsap.to("#yellow1",{
    top:"-100%",
    delay:0.5,
    duration:0.7,
    ease: "expo.out",
  })
  tl.from("#yellow2",{
    top:"100%",
     delay:1.5,
    duration:0.5,
    ease: "expo.out",
  },"anime")
  // 
  
  tl.to("#loader h1",{
    delay:1.5,
    duration:0.3,
    color:"black"
  },"anime")

  // 
  tl.to("#loader",{
    // delay:1,
    // duration:1,
    opacity:0,
    })
  tl.to("#loader",{
  
     display:"none"
    })
}




const scroll = new LocomotiveScroll({
  el: document.querySelector('#main'),
  smooth: true
});


function imageShow(){
  var page2 = document.querySelector("#page2");
var elems = document.querySelectorAll(".elem");
elems.forEach((elem)=>{
  console.log(elem)
  elem.addEventListener("mouseenter",()=>{
   var bgImage =  elem.getAttribute
   ("data-img");

  page2.style.backgroundImage= `url(${bgImage})`
  })
})
}

loading();
imageShow();


document.querySelector("#page2").addEventListener("click",()=>{
  console.log("hello")
})