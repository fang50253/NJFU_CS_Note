 // ���ظ���
 var d_open='<div class="down_detail" exposure-tag="down_detail,��ҳ���ظ���"><div class="d_open"><img class="d_qrcode"  src="https://game.gtimg.cn/images/yxzj/web201706/images/comm/floatwindow/wzry_qrcode.jpg" width="107" height="107"  alt="������Ϸ"/> </div></div> ';
 var openDiv=document.createElement('div');
 openDiv.innerHTML=d_open;
 document.body.appendChild(openDiv);
$(function() {
    // ����Ӣ��ְҵͼ�� Start
    var $heroSort = $('#hero-sort');
    if($heroSort && $heroSort.data('sort')) {
        var heroSortHtml = ''
        $.each(($heroSort.data('sort')+'').split('|'),function(index,value){
            heroSortHtml+='<i class="hero-sort hero-sort-'+value+'"></i>';
       });
       $heroSort.html(heroSortHtml);
    }
    // ����Ӣ��ְҵͼ�� End
    $('.hero-skill-intro .skill-list li').on('mouseenter', function() {
        $(this).addClass('on');
        $(this).siblings().removeClass('on');
        $(this).parent().parent().siblings('.skill-cont').find('.skill-cont-list').removeClass('on');
        $(this).parent().parent().siblings('.skill-cont').find('.skill-cont-list').eq($(this).index()).addClass('on');
    })
    $(window).scroll(function(event) {
        $('.sub-header').addClass('scrollDis');
        if ($(window).scrollTop() <= 90) {
            $('.sub-header').removeClass('scrollDis');
        }
    });
    //ê����ת����Ч��  
    $('.sub-list li a[href*=#],area[href*=#],.info-tab a[href*=#]').click(function() {
        $(this).parent('li').siblings().removeClass('on');
        $(this).parent('li').addClass('on');
        if (location.pathname.replace(/^\//, '') == this.pathname.replace(/^\//, '') && location.hostname == this.hostname) {
            var $target = $(this.hash);
            $target = $target.length && $target || $('[name=' + this.hash.slice(1) + ']');
            if ($target.length) {
                var targetOffset = $target.offset().top;
                $('html,body').animate({
                    scrollTop: targetOffset
                }, 500);
                return false;
            }
        }
    });

    //2020��7��6�� ������Ƶ����
    function TGDialogS(e){
        // ����milo������dialog���
        need("biz.dialog",function(Dialog){
            Dialog.show({
                id:e,
                bgcolor:'#000', //���������֡�����ɫ����ʽΪ"#FF6600"�����޸ģ�Ĭ��Ϊ"#fff"
                opacity:70 //���������֡���͸���ȣ���ʽΪ��10-100������ѡ
            });
        });
    }
    function closeDialog(){
        // ����milo������dialog���
        need("biz.dialog",function(Dialog){
            Dialog.hide();
        });
    }

    // ������Ƶ
    var player;
    $("body").on("click", ".player-box", function() {
        var _self = $(this).parent(),
            vid = _self.data("vid")
        if (vid) {
            player = new Txplayer({
                containerId: 'video-box',
                vid: vid,
                width: '100%',
                height: '100%',
                autoplay: true,
                platform: '8330701',
	  	        sdtfrom: 'v7102',
            });
            TGDialogS('dialog-video');
        }
    })

    //�ر���Ƶ
    $('#dialog-video .dia-close').on('click',function () {
        player.pause();
        showDialog.hide();
    });
    //2020��7��6�� ������Ƶ���� End


    //����Ӣ������
    var voice = document.getElementById('voice');
    $('#heroVoice .voice-list').on('click','li',function () {
        var voiceSrc = $(this).attr('data-voice');
        $('.voice-list').find('li').removeClass('active');
        $(this).addClass('active');
        $('#voice').attr('src',voiceSrc);
        voice.play();
    });

    //�淨˼·swiper
    var thinking = new Swiper('.thinking-swiper', {
        loop:true,
        observer:true,
        observeParents:true,
  pagination: {
      el: '.swiper-pagination',
    },
    autoplay: {
    delay: 5000,//1���л�һ��
  }
    });
})

// Ӣ��ӡ��
var heroImpression = (function () {
    var curPage = 0,
        url = {
            black : "//uic.gamesafe.qq.com/uiccgi.cgi",
            add: "//app.ingame.qq.com/php/ingame/interactcenter/add_tiny_guide.php",
            query: "//app.ingame.qq.com/php/ingame/interactcenter/query_tiny_guide_by_id.php",
            vote: "//app.ingame.qq.com/php/ingame/interactcenter/add_tiny_guide_vote.php",
            sub:"" //��¼̬�ݴ�
        },
        param = {
            game : 'smoba', //��ϷӢ����д(���绶�ֶ�������poker)
            bid : 'ingame', //ҵ��Ӣ����д
            channel: 1,     //����ID(1:΢������2��������԰��3��ͬ��վ)
            order_type: 2, //��������(1:����ʱ�� 2:����ѷ������������)
            sandbox: 0,     // ���Ի���ɳ��(1:���Ի��� 0:��ʽ����)
            works_id:''     // heroid
        },
        selector = {
            input : "#impressionTxt",
            submit : "#impressionSubmit",
            show: "div.impression-show",
            list:"ul.impression-list",
            more: "a.a-toggle-more",
            hide: "a.a-toggle-hide"
        },
        fn = {},
        util = {},
        init = function () { };
    
    // ��ȡ��¼̬
    fn.getOpenid = function (userinfo) {
        if (url.sub) { 
            var r = url.sub;
        }else if (userinfo && userinfo.logtype == "wx") {
            var r = "?appid=wx95a3a4d7c627e07d&login_type=wxm&access_token=" + milo.cookie.get("access_token") + "&openid=" + userinfo.openid;
        }else{
            var r = "?appid=1104466820&login_type=qqm&skey="+milo.cookie.get('skey')+"&uin="+milo.cookie.get('uin');
        }
        return r;
    }
    // ����¼
    util.checkLogin = function () {
        need("biz.login", function (LoginManager) {
            LoginManager.checkLogin(function (userinfo) {
                // alert("���ѵ�¼������ֱ���ύ");
                return true;
            }, function () {
                alert("��¼������ύӢ��ӡ���ǩ��");
                TGDialogS('login_select');
                return false;
                // qqAndwxLoginout();
            });
        });
    }
    // ��ѯ��ǩ
    util.queryImpress = function (heroId,gStart,gNum) {
        if(!heroId){return}
        var gNum = gNum || 10, gStart = gStart || 0;
        PTTSendClick('impression','query','��ѯ��ǩ');
        // console.log('gStart '+gStart);
        // ����������
        function ajaxQuery(userOpenid) {
            var op = userOpenid || "?not_login=1";
            $.ajax({
                method: "get",
                url: url.query + op,
                data: {
                    game : param.game,
                    bid : param.bid,
                    channel: param.channel,
                    works_id : heroId,
                    order_type : param.order_type,
                    start : gStart,
                    num: gNum,
                    sandbox : param.sandbox
                },
                dataType: "jsonp"
              }).done(function( msg ) {
                    // console.log(msg);
                    PTTSendClick('impression','queryOk','��ѯ��ǩ�ɹ�');
                    var guidelist = msg.data.guidelist,
                        html = ''
                    for (var i = 0; i < guidelist.length; i++){
                        // ��ӡӡ���б����Ͷ��Ʊ�ģ���Ǹ�class
                        html += '<li class="'+((guidelist[i].vote_info)?'voted':'')+'" data-guide="' + guidelist[i].guide_id + '">' + guidelist[i].guide_content + '</li>';
                    }
                  if (html) {
                    $(selector.show).show();
                    $(selector.list).append(html);
                      curPage += guidelist.length;
                      // console.log('curPage: ' + curPage);
                  } else if (!html && curPage > 0) {
                      PTTSendClick('impression','queryFail','��ѯ��ǩʧ��');
                      alert("���޸����ǩ��");
                  }
            });
        }
        // 
        need("biz.login", function (LoginManager) {
            LoginManager.checkLogin(function (userinfo) {
                url.sub = fn.getOpenid(userinfo);
                // ��¼�����ܱ������Ͷ��Ʊ
                ajaxQuery(url.sub);
            }, function () {
                // δ��¼���޷��������Ͷ��Ʊ
                ajaxQuery();
            });
        });
    }
    // �ύ��ǩ
    util.postImpress = function () {
        PTTSendClick('impression','post','�ύ��ǩ');
        need("biz.login", function (LoginManager) {
            LoginManager.checkLogin(function (userinfo) {
                var $txt = $(selector.input).val().trim();
                if ($txt == "") {
                    alert('��ǩ����Ϊ��');
                    return false;
                } else if ($txt.length > 6) {
                    alert('��ǩ���ܳ���6����');
                    return false;
                }
                // console.log($txt)
                // ƴװ��¼̬
                url.sub = fn.getOpenid(userinfo);
                // console.log(url.sub);
                
                // ���дʼ��
                $.ajax({
                    url:url.black,
                    data:{accounttype:0,account:0,platid:0,world:0,callbackdata:0,textcategory:0,gameid:'2645',busi_sign:'0g31L9BCFQRAR68Q6kS3',cmd:2,text:$txt},
                    dataType:"json",
                    success:function(result){
                        // console.log(result);
                        if (result.data.text_check_ret == 1) {
                            alert("���뺬�����дʣ������������ύ��");
                        } else {
                            PTTSendClick('impression','postCheckOK','�ύ��ǩ����');
                            // �ύ���ӿ�
                            // console.log("��ʼ�ύ")
                            // console.log(url.sub);?
                            $.ajax({
                                method: "get",
                                url: url.add + url.sub,
                                data: {
                                    game : param.game,
                                    bid : param.bid,
                                    channel: param.channel,
                                    works_id : param.works_id,
                                    guide_content : $txt,
                                    sandbox : param.sandbox
                                },
                                dataType: "jsonp"
                            }).done(function( msg ) {
                                // console.log(msg);
                                if (msg.status == 'SUCCESS') {
                                    alert('�ύ�ɹ���');
                                    $(selector.list).prepend('<li class="newAdd">' + $txt + '</li>');
                                    $(selector.show).show();
                                    PTTSendClick('impression','postOK','�ύ��ǩ�ɹ�');
                                } else if (msg.status == 'ERROR' && msg.code == 680907) {
                                    alert('�벻ҪƵ���ύ��ǩ��');
                                    PTTSendClick('impression','postError680907','Ƶ���ύ��ǩ');
                                } else {
                                    alert('��������ύʧ�ܣ�');
                                    PTTSendClick('impression','postError','�ύ��ǩʧ��');
                                }
                            });
                        }
                    }
                });
                PTTSendClick('impression','postLogined','�ύ��ǩ�ѵ�¼');
            }, function () {
                alert("��¼������ύӢ��ӡ���ǩ��");
                TGDialogS('login_select');
                PTTSendClick('impression','upLogined','�ύ��ǩû��¼');
                return false;
            });
        });
    }
    // �� Ӣ�۱�ǩ
    util.upImpress = function (guideId,obj) {
        if (!guideId) { return }
        PTTSendClick('impression','up','�ޱ�ǩ');
        need("biz.login", function (LoginManager) {
            LoginManager.checkLogin(function (userinfo) {
                // console.log(userinfo)
                // ƴװ��¼̬
                url.sub = fn.getOpenid(userinfo);

                // �ύ���ӿ�
                $.ajax({
                    method: "get",
                    url: url.vote + url.sub,
                    data: {
                        game : param.game,
                        bid : param.bid,
                        channel: param.channel,
                        guide_id : guideId,
                        operator_type : 1,
                        sandbox : param.sandbox
                    },
                    dataType: "jsonp"
                }).done(function( msg ) {
                    // console.log(msg);
                    if (msg.status == 'SUCCESS') {
                        alert('֧�ֳɹ���');
                        obj.addClass("voted");
                        PTTSendClick('impression','upOK','�ޱ�ǩ�ɹ�');
                    }
                    PTTSendClick('impression','upFail','�ޱ�ǩʧ��');
                });
                PTTSendClick('impression','upLogined','�ޱ�ǩ�ѵ�¼');
            }, function () {
                alert("��¼�����֧�ֱ�ǩ��");
                TGDialogS('login_select');
                PTTSendClick('impression','upUnlogin','�ޱ�ǩû��¼');
                return false;
                // qqAndwxLoginout();
             });
        });
    }
    // ���ظ���
    util.showMore = function () {
        if ($(selector.show).hasClass("show-less")) {
            $(selector.show).removeClass("show-less");
        } 
        // console.log("��ʼ�ӵ� " +curPage)
        util.queryImpress(param.works_id, curPage, 10);
        PTTSendClick('impression','showMore','�����ʾ����');
    }
    // �������
    util.showLess = function () {
        $(selector.show).addClass("show-less");
        PTTSendClick('impression','showLess','�������');
    }
    init = function (iID) {
        // �ύ��ť�¼���
        $(selector.submit).on("click", function () {
            util.postImpress();
        });
        // ���ఴť�¼���
        $(selector.more).on("click", function () {
            util.showMore();
        })
        // ����ť�¼���
        $(selector.hide).on("click", function () {
            util.showLess();
        })
        // �ޱ�ǩ�¼���
        $(selector.list).on("click","li",function () {
            if ($(this).hasClass("voted")) {
                alert("�ñ�ǩ����֧�ֹ���")
            } else if ($(this).hasClass("newAdd")) {
                alert("������ǩ�����Ժ���֧�֣�")
            } else {
                var gId = $(this).attr("data-guide");
                util.upImpress(gId,$(this));
            }
        })
        // ��ȡǰ10����ǩ
        param.works_id = iID;
        util.queryImpress(param.works_id, curPage, 10);
    }
    return {
        init:function(heroid) { init(heroid) },
    }
})();
if (impressionID) {
    heroImpression.init(impressionID);
}
