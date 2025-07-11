// 添加平滑滚动效果
document.querySelectorAll('nav a').forEach(link => {
    link.addEventListener('click', e => {
        e.preventDefault();
        const targetId = link.getAttribute('href');
        document.querySelector(targetId).scrollIntoView({
            behavior: 'smooth'
        });
    });
});

// 添加图片懒加载效果
document.addEventListener('DOMContentLoaded', function () {
    const images = document.querySelectorAll('.gallery img');
    images.forEach(img => {
        img.setAttribute('loading', 'lazy');
    });
});

// 轮播图功能
let currentSlide = 0;
const slides = document.querySelectorAll('.carousel-item');

function showNextSlide() {
    slides[currentSlide].classList.remove('active');
    currentSlide = (currentSlide + 1) % slides.length;
    slides[currentSlide].classList.add('active');
}

// 自动播放轮播图（每3秒切换一次）
setInterval(showNextSlide, 3000);
