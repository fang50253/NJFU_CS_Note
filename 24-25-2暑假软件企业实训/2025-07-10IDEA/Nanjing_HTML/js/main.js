// 添加平滑滚动功能
document.querySelectorAll('nav ul li a').forEach(anchor => {
    anchor.addEventListener('click', function (e) {
        e.preventDefault();
        const targetId = this.getAttribute('href');
        document.querySelector(targetId).scrollIntoView({
            behavior: 'smooth'
        });
        // 显示对应的二级界面
        const secondarySection = document.getElementById(targetId + '-details');
        if (secondarySection) {
            secondarySection.classList.add('active');
        }
    });
});