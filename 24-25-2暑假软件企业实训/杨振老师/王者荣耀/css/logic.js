try
{
    var wx_appid = "wxfac91dbf47418eb6";
    // var wx_appid = "wx1cd4fbe9335888fe";
    var qq_appid = "1104466820";
    var game_wx_appid = "wx95a3a4d7c627e07d";
    var game_qq_appid = "1104466820";
    var appid = '';
    var area = 0;
    var partition=0;
    var roleid='';
    var is_login = 0;
    var nickname = '';
    var log_type = '';
    var G_ROLE_DATA;
    var G_USER_INFO;
    // var rankInfo={
    //     "1":"��ǿ��ͭIII",
    //     "2":"��ǿ��ͭII",
    //     "3":"��ǿ��ͭI",
    //     "4":"�������III",
    //     "5":"�������II",
    //     "6":"�������I",
    //     "17":"��ҫ�ƽ�IV",
    //     "7":"��ҫ�ƽ�III",
    //     "8":"��ҫ�ƽ�II",
    //     "9":"��ҫ�ƽ�I",
    //     "18":"��󲬽�V",
    //     "19":"��󲬽�IV",
    //     "10":"��󲬽�III",
    //     "11":"��󲬽�II",
    //     "12":"��󲬽�I",
    //     "20":"������ʯV",
    //     "21":"������ʯIV",
    //     "13":"������ʯIII",
    //     "14":"������ʯII",
    //     "15":"������ʯI",
    //     "22":"������ҫV",
    //     "23":"������ҫIV",
    //     "24":"������ҫIII",
    //     "25":"������ҫII",
    //     "26":"������ҫI",
    //     "16":"��ҫ����"
    // };

    var ranking_star = [
        '��ǿ����', //����0��~����24��
        '��˫����', //����25��~����49��
        '��ҫ����', //����50��~����99��
        '��������', //����100�Ǽ�����
    ]

    function getRankingStarText(rankingStarId){
        rankingStarId = parseInt(rankingStarId);
        if(rankingStarId >= 0 && rankingStarId <= 24){
            return ranking_star[0]
        } else if(rankingStarId >= 25 && rankingStarId <= 49){
            return ranking_star[1]
        } else if(rankingStarId >= 50 && rankingStarId <= 99){
            return ranking_star[2]
        } else {
            return ranking_star[3]
        }
    }

    var curpro = window.location.protocol;

    function toMaxFixed(num, f) {
        if (f == null) f = 2;
        var tmp = (+num).toFixed(f);
        return +tmp;
    }

    // add by jim
    var loadHeroList = function(callback){
        $.ajax({  // ����herolist��json�ļ�
            type: "get",
            url: curpro+"//pvp.qq.com/web201605/js/herolist.json",
            dataType: "json",
            contentType: "application/json; charset=utf-8",
            success: callback,
            error: function(err) {
                alert("�ף����緱æ�����Ժ����԰�");return false;
            }
        });
    };

    // ͷ���ַ�滻
    function getHeroHeadById(heroid){
        if(heroid <= 0){
            return '';
        }
        return "//game.gtimg.cn/images/yxzj/img201606/heroimg/" + heroid + "/" + heroid + ".jpg";
    }
    
    // Ƥ��ͼƬ��ַ�滻
    function getHeroSkinById(heroid,skinid){
        if(heroid <= 0){
            return '';
        }
        return "//game.gtimg.cn/images/yxzj/img201606/heroimg/"+ heroid + "/"+ heroid +"-myskin-"+ skinid +".jpg";
    }
    
    // ���а��ַ�滻
    function getRankImgByGradeLevel(grade_level){
        if(parseInt(grade_level) <= 0){
            return '';
        }
        grade_level = parseInt(grade_level) > 26 ? 26 : parseInt(grade_level);
        return "//game.gtimg.cn/images/yxzj/web201605/page/rank" + parseInt(grade_level) + ".png";
    }
    
    // ��ȡװ��ͼƬ
    function getEquipById(equipid){
//        console.log("equipid"+equipid);
        if(equipid < 1){
            return '';
        }
        return "//game.gtimg.cn/images/yxzj/img201606/itemimg/"+ equipid +".jpg";
    }

    milo.ready(function(){
        window.iUseQQConnect = 1
        need("biz.login", function(LoginManager) {
            LoginManager.init({
                appConfig: {
                    WxAppId: wx_appid,
                    gameDomain: "pvp.qq.com"
                },
                iUseQQConnect:1,
                oQQConnectParams:{
                    appId:"101491592",
                    scope:"get_user_info",
                    state:"STATE",
                    redirect_uri:"https://milo.qq.com/comm-htdocs/login/qc_redirect.html"
                }
            });
            LoginManager.checkLogin(function (userinfo) {
                // var userinfo = result.userInfo;
                // �ѵ�¼
                is_login = 1;
                G_USER_INFO = userinfo;
                PTTSendClick("login", "logined", "�ѵ�¼");
                // ��½֮�����ص���½��
                $("#unlogin").hide();
                $("#logined_not_selected").show();
                acctype = milo.cookie.get("acctype");
                // ΢�Ż���QQ���ǳƶ����Ի�ȡ
                log_type = userinfo.logtype || userinfo.acctype;
                if (log_type == "wx" || log_type == "qc") {
                    // �û��ǳ� userinfo.nickname;
                    nickname = userinfo.nickname.replace("<script>", "&lt;script&gt;").replace("</script>", "&lt;/script&gt;");
                    if (nickname.length >= 6) {
                        nickname = nickname.substr(0, 6) + "...";
                    }
                    $("#nickname").html(nickname);
                    // $(".info-id label").text(userinfo.nickname);
                    newGetPic(userinfo);
                }
                // 1��Q��׿��2��QIOS��3΢�Ű�׿��4΢��IOS
                var server_select_url = curpro + "//pvp.qq.com/comm-htdocs/js/game_area/yxzj_WX_server_select.js";
                if (log_type == "qc") {
                    server_select_url = curpro + "//pvp.qq.com/comm-htdocs/js/game_area/yxzj_SQ_server_select.js";
                    appid = qq_appid;
                } else {
                    appid = wx_appid;
                }
                include(server_select_url + "?_rand=" + Math.random(), function () {
                    checkLoop();
                    $(".select_role").click(function () {
                        TGDialogS("area_select");
                    });
                });

                // TODO:���ش�����Ϣ
                var ROLE_KEY = milo.cookie.get("openid");
                if (log_type == "qc") {
                    ROLE_KEY = milo.cookie.get("uin");
                }
                // var data = {"area":area, "partition":partition, "roleid":roleid};
                var data = milo.cookie.get("PVP_PERSONAL_DATA_" + ROLE_KEY);
                // 7�����
                if (data) {
                    // console.log(data);
                    G_ROLE_DATA = milo.unSerialize(data);
                    // console.log(G_ROLE_DATA);
                    area = G_ROLE_DATA.areaid;
                    partition = G_ROLE_DATA.sPartition;
                    roleid = G_ROLE_DATA.roleid;

                    $("#logined_not_selected").hide();
                    $("#logined_selected").show();
                    $("#area_info").text(G_ROLE_DATA.rolename + " [" + G_ROLE_DATA.areaname + "]");
                    $(".info-id label").text(G_ROLE_DATA.rolename);
                    var pathname = window.location.pathname;
                    if (pathname.indexOf("hisrecord") >= 0) {
                        // GetHisRecord();// ��ʷս��
                        IDE_GetHisRecord();
                    } else if (pathname.indexOf("artdetail") >= 0) {
                        // GetHeroSkin();  // �ҵ��ʲ�
                        IDE_GetHeroSkin();
                    } else {
                        // GetGameInfo();  // ������Ϣ
                        IDE_GetGameInfo();
                    }
                }
                else {
                    var pathname = window.location.pathname;
                    if (pathname.indexOf("personal") >= 0 || pathname.indexOf("hisrecord") >= 0 || pathname.indexOf("artdetail") >= 0) {
                        TGDialogS("area_select");
                    }
                }
                var pathname = window.location.pathname;
                if (pathname == "/" || pathname == "/index.shtml") {
                    PTTSendClick("state", "logined", "��½");
                }
                // console.log(userinfo);

                // add by sonichuang 2018-04-08(Market demand: userinfo Reported) ---------------------------------------------
                // app.ingame.qq.com/php/ingame/useraction/user_action_pc.php?openid=test&duration=100&acctype=1&platid=1&zoneid=100&playerid=111&nowpage=test&topage=test&sourceid=ttt&actionid=12
                var uInfoRep = {};
                if (log_type == "wx") {
                    uInfoRep.acctype = 1;
                    uInfoRep.openid = G_USER_INFO.openid || G_USER_INFO.userUin || G_USER_INFO.uin;
                    // uInfoRep.platid = (G_ROLE_DATA && G_ROLE_DATA.areaid ==3) ? 1 : 0;
                    if (G_ROLE_DATA) {
                        uInfoRep.platid = (G_ROLE_DATA.areaid == 3) ? 1 : 0;
                    } else {
                        uInfoRep.platid = 2
                    }
                } else {
                    uInfoRep.acctype = 2;
                    uInfoRep.openid = G_USER_INFO.userUin || G_USER_INFO.uin;
                    if (G_ROLE_DATA) {
                        uInfoRep.platid = (G_ROLE_DATA.areaid == 1) ? 1 : 0;
                    } else {
                        uInfoRep.platid = 2
                    }
                }
                uInfoRep.zoneid = (G_ROLE_DATA && G_ROLE_DATA.sPartition) ? G_ROLE_DATA.sPartition : 0;
                uInfoRep.playerid = (G_ROLE_DATA && G_ROLE_DATA.checkparam.split("|")[2]) ? G_ROLE_DATA.checkparam.split("|")[2] : 0;
                uInfoRep.nowpage = (setSite) ? "PC-" + setSite.pageType : "unknow";
                uInfoRep.topage = "unknow";
                uInfoRep.sourceid = 9;
                uInfoRep.duration = 0;
                uInfoRep.actionid = 0;
                // console.log(uInfoRep);
                $.ajax({
                    dataType: "jsonp",
                    url: "//app.ingame.qq.com/php/ingame/useraction/user_action_pc.php",
                    data: uInfoRep
                }).done(function (msg) {
                    console.log("userinfo Reported Success!" + msg.msg);
                });
                // End 2018-04-08-----------------------------------------------------------------------------------------------
            }, function () {
                qqAndwxLoginout();
                if (location.pathname === "/web201605/personal.shtml"
                    || location.pathname === "/web201605/hisrecord.shtml"
                    || location.pathname === "/web201605/artdetail.shtml") {
                    setTimeout(function () { 
                        bindQQAndWX();
                        TGDialogS("login_select");
                    }, 500);
                }
                // bandQQAndWX();
            });
        });
        $(".logout_btn").on("click", function(){
            qqAndwxLoginout();
            $("#logined_selected").hide();
            $("#logined_not_selected").hide();
            $("#unlogin").hide();
            $("#area_info").text("--");
            $(".avatar img").attr("src", "//game.gtimg.cn/images/yxzj/web201605/main/avatar1.jpg");
        });
    });
    
    // JS��ȡͷ�� replace by jim
    function newGetPic(userinfo){
        var image_url = "//game.gtimg.cn/images/yxzj/web201605/main/avatar1.jpg";
        if (log_type == "wx") {
            if (userinfo.headimgurl != "") {
                image_url = userinfo.headimgurl + "/96";
            }
            $(".avatar img").attr("src", image_url);
            $(".info-pho img").attr("src", image_url);
        } else if (log_type == "qc") {
            LoginManager.getUserFace(function(sAvatar){
                console.log('ͷ��Ϊ��',sAvatar);
                image_url = sAvatar
                $(".avatar img").attr("src", image_url);
                $(".info-pho img").attr("src", image_url);
            })
            // image_url = location.protocol + "//q.qlogo.cn/g?b=qq&nk=" + userinfo.uin + "&s=100";
        }
        // var image_url = userinfo.avatarUrl;


    }

    // ע����¼
    function qqAndwxLoginout(){
        need("biz.login", function(LoginManager){
            LoginManager.logout(function(){
                console.log("��¼ע���ɹ�");
            },{
                showTip: false
            });
            
            milo.cookie.clear("p_skey", "qq.com", "/");
            milo.cookie.clear("p_uin", "qq.com", "/");
            milo.cookie.clear("uin", "qq.com", "/");
            milo.cookie.clear("skey", "qq.com", "/");


            milo.cookie.clear("IED_LOG_INFO2");
            milo.cookie.clear("IED_LOG_INFO2", "qq.com", "/");

            milo.cookie.clear("openid", "qq.com", "/");
            milo.cookie.clear("access_token", "qq.com", "/");
            milo.cookie.clear("acctype", "qq.com", "/");
            milo.cookie.clear("appid", "qq.com", "/");


            milo.cookie.clear("openid");
            milo.cookie.clear("access_token");
            milo.cookie.clear("acctype");
            milo.cookie.clear("appid");

            milo.cookie.clear("PVP_PERSONAL_HERO", "qq.com", "/");

            window["logoutWxCallback"] = function(){
                $("#_overlay_").hide();
                $("#_PopupMsg_").hide();
            }

            var oWxIFrame = document.createElement("iframe");
            oWxIFrame.id = "loginWxIframe";
            oWxIFrame.name = "loginWxIframe";
            oWxIFrame.scrolling="no";
            oWxIFrame.frameBorder ="0";
            oWxIFrame.style.display ="none";
            document.body.appendChild(oWxIFrame);
            oWxIFrame.src=curpro+"//apps.game.qq.com/ams/logout_wx.html";

            // �ǳ�qq�������game.qq.com�µ�cookie
            /*window["logoutCallback"] = function(){
                $("#_overlay_").hide();
                $("#_PopupMsg_").hide();
            }*/

            var oIFrame = document.createElement("iframe");
            oIFrame.id = "loginIframe";
            oIFrame.name = "loginIframe";
            oIFrame.scrolling="no";
            oIFrame.frameBorder ="0";
            oIFrame.style.display ="none";
            document.body.appendChild(oIFrame);
            oIFrame.src=curpro+"//game.qq.com/act/logout.html?t=1";
            // bandQQAndWX();
            // alert("test");
        });
    }

    bindQQAndWX();
    // �󶨵�¼��ʽ�İ�ť����¼�
    function bindQQAndWX(){
        need("biz.login", function (LoginManager) {
            // �󶨵�½����
            $("#qqlogin").off().on("click", function () {
                LoginManager.login({
                    iUseQQConnect:1
                });
                window.showDialog && window.showDialog.hide();
            });
            $("#wxlogin").off().on("click", function () {
                LoginManager.loginByWx({
                    "appId": wx_appid
                });
            });
        });
        // $("#qqlogin").off().on("click", function() {
        //     IDE.loginByQQ();
        //     window.showDialog && window.showDialog.hide();
        // });
        // $("#wxlogin").off().on("click", function() {
        //     IDE.loginByWX({
        //         appId: wx_appid,
        //     });
        //     window.showDialog && window.showDialog.hide();
        // });
    }

// qq������¼��ʽ��UI�㼶�����⣬�����ø߲㼶����Ȼ�ᱻ�ڵ�
    (function(){
        var style = document.createElement('style');
        style.innerHTML = '.qConnectLogin {z-index: 99;}';
        document.head.appendChild(style);
    })()

    window.iCloseMiloPIP = 1 // �ر�milo�Ľ�ɫѡ��ʱ����Ȩ����
    function checkLoop(userinfo){
        
        need(["biz.roleselector"],function(RoleSelector){
          var roleobj = cloneClass(RoleSelector);
          // var roleobj = RoleSelector;
              
          roleobj.init({
			openToOpen:{
                "sAMSTrusteeship": 1,
                "ams_targetappid_wx" : game_wx_appid,  // ��Ҫ����openidת������Ϸҵ��appid������ʵ������޸�
                "ams_targetappid_qc":game_qq_appid
            },
            "type" : "html",
            "gameId" : "yxzj",
            "isQueryRole" : true,
            "isShutdownSubmit" : false,
            
            "areaContentId" : "areaContentId",
            "channelContentId" : "channelContentId", // ����ò�������ɾ��
            // "systemContentId" : "systemContentId",   // ����ò�������ɾ��
            "roleContentId" : "roleContentId",
            "confirmButtonId" : "RoleSelectBtn",
            
            "submitEvent" : function(roleObj){
                // ѡ�����ɫ�����ȷ����ťʱ�ᴥ��
                if(!$("#se-checkbox").is(":checked")) {
                    // �Ƿ����˸�����Ϣ
                    alert("����ͬ����Ȩ")
                    return
                }
                window.showDialog && window.showDialog.hide(); // �رս�ɫѡ�񵯴�

                G_ROLE_DATA = roleObj.submitData;
                // ���ɫ����
                console.log("roleObj", JSON.stringify(roleObj));
                localStorage.setItem("roleObj", JSON.stringify(roleObj));
                localStorage.setItem("roleid", roleObj.submitData.roleid);
                // console.log(G_ROLE_DATA);
                area = G_ROLE_DATA.areaid;
                partition = G_ROLE_DATA.sPartition;
                roleid = G_ROLE_DATA.roleid;
                // TODO:��������Ϣ
                var ROLE_KEY = milo.cookie.get("openid");
                if(log_type == "qc")
                {
                    ROLE_KEY = milo.cookie.get("uin");
                }
                milo.cookie.set("PVP_PERSONAL_DATA_"+ROLE_KEY, milo.serialize(G_ROLE_DATA), 60*60*24*7,"pvp.qq.com","/"); // 7�����
                // console.log("PVP_PERSONAL_DATA_"+ROLE_KEY);

                $("#logined_not_selected").hide();
                $("#logined_selected").show();
                $("#area_info").text(G_ROLE_DATA.rolename + " [" + G_ROLE_DATA.areaname + "]");
                $(".info-id label").text(G_ROLE_DATA.rolename);
                /*
                amsCfg_262097.sData.sPlatId = roleObj.submitData.sPlatId;
                amsCfg_262097.sData.sPartition = roleObj.submitData.sPartition;
                amsCfg_262097.sData.sArea = roleObj.submitData.areaid;
                amsCfg_262097.sData.sRoleId = roleObj.submitData.roleid;
                */
                var pathname = window.location.pathname;
                if(pathname == "/web201605/hisrecord.shtml"){  // ��ʷս��
                    // GetHisRecord();
                    IDE_GetHisRecord();
                }else if(pathname == "/web201605/artdetail.shtml"){  // �ҵ��ʲ�
                    // GetHeroSkin();
                    IDE_GetHeroSkin();
                }else{
                    // GetGameInfo();
                    IDE_GetGameInfo();
                }

                PTTSendClick("login", "loginseted", "��ѡ����");
                if(pathname == "/" || pathname == "/index.shtml"){
                    PTTSendClick("login", "indexseted", "��ҳѡ�����");
                }

                // ��ҳ���ṩ��¼�ɹ���Ļص�
                typeof window.loginCallbackFn === "function" && window.loginCallbackFn(roleObj);
            },
            "openEvent" : function(){// �򿪴���ʱִ�еķ���
            },
            "cancelEvent" : function(){// ���ȡ���Ļص�����
            },
            "closeEvent" : function(){// ����رյĻص�����
            }
          });
          
          roleobj.show();
        });
    }

    // չʾ�״�ͼ����
    function DrawSpider(data)
    {
        // include("//pvp.qq.com/web201605/js/chart.js", function(loaded){
            for(i in data)
            {
                // data[i] = Math.round(data[i]/10);
                // TODO: ��������ʾ
                data[i] = Math.round(parseInt(data[i])/1000);
                if(data[i] > 10){
                    data[i] = 10;
                }
            }
           console.log(data);

            var dataChart = {
                // labels: ["KDA", "����", "��ս", "����", "���"],
                labels: ["���", "KDA", "����", "��ս", "����"],
                datasets: [
                    {
                        label: "My First dataset",
                        fillColor: "rgba(79,181,247,0.6)",
                        strokeColor: "rgba(79,181,247,1)",
                        // data: [data.kda, data.survive, data.battle, data.grow, data.hurt_hero]
                        data: [data.hurt_hero, data.kda, data.grow, data.battle, data.survive]
                        // <!--data : [65,59,90,81,56,55]-->
                    }
                ]
            };

            if(document.getElementById("radar")){ // ���汨��ִ��ʱ�ж������޴�Ԫ��(Modify by sonichuang 2017-06-07)
                var ctx = document.getElementById("radar").getContext("2d");
                var myRadarChart = new Chart(ctx).Radar(dataChart,{
                    pointDot:true,
                    angleLineColor:"rgba(190,201,214,1)",
                    scaleLineColor:"rgba(190,201,214,1)",
                    pointLabelFontColor:"#999",
                    angleShowLineOut:true,
                    angleLineWidth : 1,
                    scaleLineWidth : 1,
                    pointLabelFontSize:"20",
                    scaleOverlay:false,
                    scaleOverride : true,
                    scaleSteps : 5,
                    scaleStartValue: 0,
                    scaleStepWidth : 2,
                    maintainAspectRatio: false,
                    responsive: true,
                });
            }

        // });
    }
    
    // ͷ����Ϣ
    function GetHeadInfo()
    {
        var url = curpro+"//mapps.game.qq.com/yxzj/web201605/GetHeroSkin.php?appid="+appid+"&area="+area+"&partition="+partition + "&roleid=" + roleid +"&r="+Math.random();
        include(url, function(loaded){
            if(!loaded || typeof(GetHeroSkinResult) == "undefined")
            {
                alert("ϵͳ��æ�����Ժ�����");
                return;
            }
            // console.log(loaded);
            var result = GetHeroSkinResult;
            if(result.iRet != 0)
            {
                alert(result.sMsg);
                return;
            }
            
            // todo test  �ÿ�
            if(typeof(result.data.history) != "undefined" && typeof(result.data.hero_skin_list) != "undefined")
            {
                // �ܱ���ʤ����ʤ�ʣ� ��λ��ʤ��ʤ��
                $(".win_count").text(result.data.history.total_win_num);
                $(".hero_count").text(result.data.hero_skin_list.HeroListCount);
                $(".skin_count").text(result.data.hero_skin_list.HeroSkinCount);
            }
        });
    }

    function IDE_GetHeadInfo(detail, onSuccess) {
        IDE.emit({
            actId: "5_VaG4AS",
            token: "kvlozj",
            loading: true, // ����loading����,Ĭ�ϲ�����
            sData: { sArea: area, sPlatId: [2, 4].indexOf(+area) ? 0 : 1, sPartition: partition, detail: detail },
            openToOpen: { sAMSTrusteeship: 1, ams_targetappid_wx: game_wx_appid, ams_targetappid_qc: game_qq_appid },
            success: function (result) {
                console.log("�ɹ���ȡӢ��Ƥ����Ϣ", result);
                $(".hero_count").text(result.data.hero_count);
                $(".skin_count").text(result.data.skin_count);
                // var skinCount = 0
                // for (var sk in result.data.skins){
                //     if(parseInt(sk) > 0){
                //         skinCount += parseInt(result.data.skins[sk])
                //     }
                // }

                // ������Ϣ
                if(result.data.user != null) {
                    var user = result.data.user;
                    $(".level-ico").text(user.pvplevel);
                    var grade_level = +user.grade_level || 1;
                    if(grade_level < 1) grade_level = 1; // ���û�����λ��ʹ����ͭIIIͼƬ
                    $(".grade_level").text(getRankingStarText(user.ranking_star))//rankInfo[String(grade_level)]);
                    $(".sco-img").attr("src", getRankImgByGradeLevel(grade_level));
                    $(".credit_value").text(user.credit_value);
                    $(".info-id span").text("(" + (decodeURIComponent(user.team_name) || "��ս����Ϣ") + ")");
                }
                // �Ծ���Ϣ
                if (result.data.battle != null) {
                    var battle = result.data.battle;
                    // $(".win_count").text(battle.total_win_num);
                    $(".ladder_win_rate").text(toMaxFixed(battle.ladder_win_rate, 1));
                    $(".total_count").text(battle.show_total_num);
                    $(".win_count").text(battle.total_win_num);
                    $(".win_rate").text(toMaxFixed(battle.total_win_rate, 1));
                    $(".qua_count").text(battle.ladder_count);
                    $(".quawin_count").text(battle.ladder_win_num);
                    $(".quawin_rate").text(toMaxFixed(battle.ladder_win_rate, 1));
                }
                if (onSuccess instanceof Function) onSuccess(result);
            },
            fail: function (result) {
                console.error("Ӣ��Ƥ����Ϣ��ȡʧ��", result);
                if (result.iRet === 101 || result.iRet === "101") {
                    // todo ��¼̬ʧЧ����Ҫ���µ���¼���� ����������ʵ�֣�
                    alert("�����µ�¼��");
                    TGDialogS("login_select");
                } else {
                    alert("ϵͳ��æ�����Ժ�����"); // alert("����ʧ�ܣ�" + res.sMsg);
                }
            }
        });
    }

    // ������Ϣ
    function GetGameInfo()
    {
        GetHeadInfo();

        var url = curpro+"//mapps.game.qq.com/yxzj/web201605/GetGameInfo.php?appid="+appid+"&area="+area+"&partition="+partition + "&roleid=" + roleid +"&r="+Math.random();
        include(url, function(loaded) {
            if(!loaded || typeof(result) == "undefined")
            {
                alert("ϵͳ��æ�����Ժ�����");
                return;
            }
            // console.log(loaded);
            // console.log(data);
            if(result.iRet != 0)
            {
                alert(result.sMsg);
                return;
            }
            
            // todo test  �����ÿտ�Ч��
            // ��������
            if(typeof(result.data.score) != "undefined")
            {
//                $(".sco-dec b").text((result.data.score > 100) ? 100 : result.data.score);
                var integImg_url = curpro+"//mapps.game.qq.com/yxzj/web201605/getIntegDataImg.php?appid="+appid+"&area="+area+"&partition="+partition + "&position=2"+"&r="+Math.random();
                $("#score_grade").attr("src",integImg_url);

            }

            if(typeof(result.data.idip_info) != "undefined")
            {
                $(".level-ico").text(result.data.idip_info.pvplevel);
                // ΢�ź���QͼƬ���޷�����
                // $(".avatar img").attr("src", decodeURIComponent(result.data.idip_info.head_url));
                // $("#nickname").text(decodeURIComponent(result.data.idip_info.charac_name));
                
                grade_level = (result.data.idip_info.grade_level) ? result.data.idip_info.grade_level : 1;
                // alert(rankInfo[grade_level]);
                $(".grade_level").text(rankInfo[grade_level]);
                var img_level = parseInt(grade_level);
				if(img_level < 1) img_level = 1; // ���û�����λ��ʹ����ͭIIIͼƬ
                var grade_level_url = getRankImgByGradeLevel(img_level);
                $(".sco-img").attr("src", grade_level_url); 
                /* IDIP����
                if(result.data.idip_info.play_time >= 0)
                {
                    var time = Math.floor(result.data.idip_info.play_time/3600);
                    $(".play_time").text(time);
                }
                */
                var team = "��ս����Ϣ";
                if(result.data.idip_info.team != 0 && result.data.idip_info.team != '')
                {
                    team = decodeURIComponent(result.data.idip_info.team);
                }
                $(".info-id span").text("(" + team + ")");
            }

//            if(typeof(result.data.ic_info) != "undefined")
//            {
//            }
            // �״�ͼ ��ֵΪ1-6
            // data.kda, data.survive, data.battle, data.grow, data.hurt_hero, data.push
            if(typeof(result.data.spider) != "undefined")
            {
                console.log("result.data.spider: ");
                console.log(result.data.spider);
                DrawSpider(result.data.spider);
            }

            // ����Ӣ�۴��桢seventh
//            if(typeof(result.data.ic_hero_info.herolist) != "undefined"){
//                var userUseHero = [];
//                $.each(result.data.ic_hero_info.herolist,function(i,hero){
//                    userUseHero.push(hero.heroid);
//                });
//                if(userUseHero.length > 0){
//                    var info = userUseHero.join("_") + "_i_" + result.data.idip_info.uid;
//                    milo.cookie.set("PVP_PERSONAL_HERO", milo.serialize(info), 60*60*24*7,"pvp.qq.com","/"); // 7�����
//                }
//
//                var pathname = window.location.pathname;
//                if(pathname == "/" || pathname == "/index.shtml" ){
//                    PTTSendClick("state","userhero","��ҳ���Ӣ��");
//                }
//
//            }


            // �ۺ�����
            if(typeof(result.data.history) != "undefined")
            {
                // ��ս����
//                for(i in result.data.history)
//                {
//                    result.data.history[i] = parseInt(result.data.history[i]);
//                }
                var integImg_url2 = curpro+"//mapps.game.qq.com/yxzj/web201605/getIntegDataImg.php?appid="+appid+"&area="+area+"&partition="+partition + "&position=1"+"&r="+Math.random();
                $("#intedata").attr("src",integImg_url2);
                
//                

                // ��λʤ��
//                var total = result.data.history.ladder_win_num + result.data.history.ladder_lose_num;
//                var quawin_rate = (total > 0) ? result.data.history.ladder_win_num * 100 / total : 0;
//                $(".quawin_rate").text(quawin_rate.toFixed(1));
//                $(".qua_count").text(total);
//                $(".quawin_count").text(result.data.history.ladder_win_num);
//
//                // ȫ������ʤ��
//                total = result.data.history.total_win_num + result.data.history.total_lose_num;
//                var total_rate = (total > 0) ? result.data.history.total_win_num * 100 / total : 0;
//                $(".total_count").text(total);
//                $(".win_count").text(result.data.history.total_win_num);
//                $(".win_rate").text(total_rate.toFixed(1));
                
                  // ��Ӣ����ϸʤ�ʣ�������         
//                total = result.data.history["one_vs_one_lose_num"] + result.data.history["one_vs_one_win_num"];
//                $(".tr1v1 td:eq(1)").text(total);
//                $(".tr1v1 td:eq(2)").text(result.data.history["one_vs_one_win_num"]);
//                if(total > 0)
//                {
//                    var rate = Math.floor(result.data.history["one_vs_one_win_num"] * 100 / total);
//                    $(".tr1v1 td:eq(3)").text(rate + "%");
//                }
//                
//                total = result.data.history["three_vs_three_lose_num"] + result.data.history["three_vs_three_win_num"];
//                $(".tr3v3 td:eq(1)").text(total);
//                $(".tr3v3 td:eq(2)").text(result.data.history["three_vs_three_win_num"]);
//                if(total > 0)
//                {
//                    rate = Math.floor(result.data.history["three_vs_three_win_num"] * 100 / total);
//                    $(".tr3v3 td:eq(3)").text(rate + "%");
//                }
//
//                total = result.data.history["five_vs_five_lose_num"] + result.data.history["five_vs_five_win_num"];
//                $(".tr5v5 td:eq(1)").text(total);
//                $(".tr5v5 td:eq(2)").text(result.data.history["five_vs_five_win_num"]);
//                if(total > 0)
//                {
//                    rate = Math.floor(result.data.history["five_vs_five_win_num"] * 100 / total);
//                    $(".tr5v5 td:eq(3)").text(rate + "%");
//                }
            }

            // ��߼�¼
//            $(".highestwin").text(result.data.ic_info.highestwin);
//            $(".highestfail").text(result.data.ic_info.highestfail);
//            var win_info = [
//                result.data.ic_info.highestkill,
//                result.data.ic_info.highestdeath,
//                result.data.ic_info.highestassist,
//                result.data.ic_info.highestmoney,
//                result.data.ic_info.highestexport,
//            ];
//
//            var fail_info = [
//                result.data.ic_info.highestbear,
//                result.data.ic_info.godlike,
//                result.data.ic_info.mvp,
//                result.data.ic_info.firstblood,
//                result.data.ic_info.fivekill,
//            ];
//            var win_obj = $(".highestwin_info");
//            var fail_obj = $(".highestfail_info");
//            for(i=0; i < win_info.length; i++)
//            {
//                win_obj.find("span:eq(" + i + ")").text(win_info[i]);
//            }
//            for(i=0; i < fail_info.length; i++)
//            {
//                fail_obj.find("span:eq(" + i + ")").text(fail_info[i]);
//            }

            // ����ս��, �������ݼ���Ӧ���ֵ
//            var last_week = [
//                [result.data.ic_info.lastweekwin, 100],
//                [result.data.ic_info.lastweekwin, result.data.ic_info.lastweektotal],
//                [result.data.ic_info.lastweekkill, 1000],
//                [result.data.ic_info.lastweekdeath, 600],
//                [result.data.ic_info.lastweekassist, 1200]
//            ];
//            var last_week_obj = $(".rec-list");
//            for(var i=0; i < last_week.length; i++)
//            {
//                // $(".rec-list").find("li:eq(0) p")
//                var tmp_obj = last_week_obj.find("li:eq(" + i + ")");
//                if(i==1) // ����ʤ������ʤ��
//                {
//
//                    var win_rate = 0;
//                    if(result.data.ic_info.lastweektotal > 0)
//                    {
//                        win_rate = Math.floor(result.data.ic_info.lastweekwin *100 / result.data.ic_info.lastweektotal);
//                    }
//                    tmp_obj.find("p span").text(win_rate + "%");
//                    tmp_obj.find("p:eq(1)").attr("style", "width:" + win_rate + "%");
//                }
//                else
//                {
//                    var comp_with_max = last_week[i][0] > last_week[i][1] ? last_week[i][1] : last_week[i][0];
//                    var rate = Math.ceil(comp_with_max * 100 / last_week[i][1]);
//
//                    tmp_obj.find("p span").text(comp_with_max);
//                    tmp_obj.find("p:eq(1)").attr("style", "width:" + rate + "%");
//                }
//            }
        });
    }

    function IDE_GetGameInfo() {
        IDE_GetHeadInfo(1);

        IDE.emit({
            actId: "5_VaG4AS",
            token: "fsnzuA",
            loading: true, // ����loading����,Ĭ�ϲ�����
            sData: { sArea: area, sPlatId: [2, 4].indexOf(+area) ? 0 : 1, sPartition: partition },
            openToOpen: { sAMSTrusteeship: 1, ams_targetappid_wx: game_wx_appid, ams_targetappid_qc: game_qq_appid },
            success: function (result) {
                console.log("�ɹ���ȡ�û���Ϣ", result);
                // ������Ϣ
                if(result.data.user != null) {
                    var user = result.data.user;
                    $(".level-ico").text(user.pvplevel);
                    var grade_level = +user.grade_level || 1;
                    if(grade_level < 1) grade_level = 1; // ���û�����λ��ʹ����ͭIIIͼƬ
                    $(".grade_level").text(getRankingStarText(user.ranking_star))//rankInfo[String(grade_level)]);
                    $(".sco-img").attr("src", getRankImgByGradeLevel(grade_level));
                    $(".credit_value").text(user.credit_value);
                    $(".info-id span").text("(" + (decodeURIComponent(user.team_name) || "��ս����Ϣ") + ")");
                }
                // �Ծ���Ϣ
                if (result.data.battle != null) {
                    var battle = result.data.battle;
                    // $(".win_count").text(battle.total_win_num);
                    $(".ladder_win_rate").text(toMaxFixed(battle.ladder_win_rate, 1));
                    $(".total_count").text(battle.show_total_num);
                    $(".win_count").text(battle.total_win_num);
                    $(".win_rate").text(toMaxFixed(battle.total_win_rate, 1));
                    $(".qua_count").text(battle.ladder_count);
                    $(".quawin_count").text(battle.ladder_win_num);
                    $(".quawin_rate").text(toMaxFixed(battle.ladder_win_rate, 1));
                }
                // �״�ͼ ��ֵΪ1-6
                // data.kda, data.survive, data.battle, data.grow, data.hurt_hero, data.push
                if(result.data.spider != null) DrawSpider(result.data.spider);
            },
            fail: function (result) {
                console.error("�û���Ϣ��ȡʧ��", result);
                if (result.iRet === 101 || result.iRet === "101") {
                    // todo ��¼̬ʧЧ����Ҫ���µ���¼���� ����������ʵ�֣�
                    alert("�����µ�¼��");
                    TGDialogS("login_select");
                } else {
                    alert("ϵͳ��æ�����Ժ�����");
                    // alert("����ʧ�ܣ�" + res.sMsg);
                }
            }
        });
    }

    // ��ʷս��
    function GetHisRecord()
    {
        GetHeadInfo();

        var url = curpro+"//mapps.game.qq.com/yxzj/web201605/GetHisRecord.php?appid="+appid+"&area="+area+"&partition="+partition + "&roleid=" + roleid +"&r="+Math.random();
        include(url, function(loaded){
            if(!loaded || typeof(result) == "undefined")
            {
                alert("ϵͳ��æ�����Ժ�����");
                return;
            }
            // console.log(loaded);
            if(result.iRet != 0)
            {
                alert(result.sMsg);
                return;
            }

            if(typeof(result.data.idip_info) != "undefined")
            {
                $(".level-ico").text(result.data.idip_info.pvplevel);
                // ΢�ź���QͼƬ���޷�����
                // $(".avatar img").attr("src", decodeURIComponent(result.data.idip_info.head_url));
                // $("#nickname").text(decodeURIComponent(result.data.idip_info.charac_name));
                
                grade_level = (result.data.idip_info.grade_level) ? result.data.idip_info.grade_level : 1;
                // alert(rankInfo[grade_level]);
                $(".grade_level").text(rankInfo[grade_level]);
//                var img_level = parseInt(grade_level);
//				if(img_level < 1) $img_level = 1;
//                var grade_level_url = getRankImgByGradeLevel(img_level);
//                $(".sco-img").attr("src", grade_level_url);
                /* IDIP����
                if(result.data.idip_info.play_time >= 0)
                {
                    var time = Math.floor(result.data.idip_info.play_time/3600);
                    $(".play_time").text(time);
                }
                */
//                var team = "��ս����Ϣ";
//                if(result.data.idip_info.team != 0 && result.data.idip_info.team != '')
//                {
//                    team = decodeURIComponent(result.data.idip_info.team);
//                }
//                $(".info-id span").text("(" + team + ")");
            }

            if(typeof(result.data.his_record) != "undefined")
            {
                // todo test �ÿ�
                //            
                // ���һ�α���
                var his_last1 = result.data.his_record[0];
                var his_last10 = result.data.his_record;

                var his_info = 0+"|"+his_last1.GameSeq+"|"+his_last1.GameSvrEntity+"|"+his_last1.RelaySvrEntity+"|"+his_last1.LineType+"|"+his_last1.Camp1Num;
                $("#his_last_linfo1").find(".his_info_arrow").attr("data-id", his_info);
                var img = getHeroHeadById(his_last1.HeroID1);
                $("#his_last_linfo1 .his_headimg").attr("src", img);
                $("#his_last_linfo1 .pvplevel").text("LV."+his_last1.PvpLevel);
                if(his_last1.GameResult == 1){
                    $("#his_last_linfo1 .his_info_m_txt").removeClass("_faltxt").addClass("_suctxt").text("ʤ��");
                }else{
                    $("#his_last_linfo1 .his_info_m_txt").removeClass("_suctxt").addClass("_faltxt").text("ʧ��");
                }
                // �Ծ�ģʽ
                $("#his_last_linfo1 .his_info_m_maptxt").text(his_last1.GameTypeName);
                $("#his_last_linfo1 .gameduration").text(Math.round(parseInt(his_last1.UsedTime)/60));
                var kda = his_last1.KDA;
				if(his_last1.GradeOfRank < 1) his_last1.GradeOfRank = 1;
                var grade_level_url = getRankImgByGradeLevel(his_last1.GradeOfRank);
                $("#his_last_linfo1 .his_info_dan").attr("src", grade_level_url);
                
                // ��߷���  todo deal
                var hisImg_url = curpro+"//mapps.game.qq.com/yxzj/web201605/getHistoryImg.php?appid="+appid+"&area="+area+"&partition="+partition +"&r="+Math.random();
                $(".hisdata").eq(0).css("background","url("+hisImg_url+")");
                
                
//                $("#his_last_linfo1 .info_kda").text(" KDA:"+kda.toFixed(1));
//                $("#his_last_linfo1 .killnum").text(his_last1.KillCnt);
//                $("#his_last_linfo1 .deathnum").text(his_last1.DeadCnt);
//                $("#his_last_linfo1 .assistnum").text(his_last1.AssistCnt);
                
                $("#his_last_linfo1 .equipment_time").text(his_last1.GameSeqDateTime);
                // ���ճ�װ
                var equip_str = his_last1.FinalInBattleEquipStr.split(",");
                var equip_str_html = '';
                if(equip_str.length > 0){
                    $.each(equip_str, function(k, v){
                        v = v.split("+");
                        if(v[0] > 0){
                            var equip_url = getEquipById(v[0]);
                            equip_str_html += '<img width="50" height="50" src="'+equip_url+'">';
                        }
                    });
                }
                $("#his_last_linfo1 .equipment_imglist").html(equip_str_html);
                // ����
                $("#his_last_linfo1 .mvp_num").text(his_last1.score);
                // �Ƿ�MVP
                if(his_last1.MvpCnt == 1){
                    $("#his_last_linfo1 .his_info_mvp").show();
                }else{
                    $("#his_last_linfo1 .his_info_mvp").hide();
                }

                $("#his_last_linfo1").show();

                // ��ʷս��
                var num = '';
                $.each(his_last10, function(k, v){
                    if(k == 0){
                        return;
                    }
                    num = k;
                    next_num = num + 1;
                    var obj = $("#his_last_game10_"+num).clone(true);
                    obj.attr("id", "his_last_game10_"+next_num);

                    obj.insertAfter("#his_lastgame_detail_"+num);

                    var his_info = num+"|"+v.GameSeq+"|"+v.GameSvrEntity+"|"+v.RelaySvrEntity+"|"+v.LineType+"|"+v.Camp1Num;
                    $("#his_last_game10_"+num).find(".his_info_arrow").attr("data-id", his_info);

                    var obj_detail = $("#his_lastgame_detail_"+num).clone(true);
                    obj_detail.attr("id", "his_lastgame_detail_"+next_num);
                    obj_detail.find(".item_succ_i").attr("id", "item_i_succ_"+next_num+"_"+1);
                    obj_detail.find(".item_fail_i").attr("id", "item_i_fail_"+next_num+"_"+1);
                    obj_detail.insertAfter("#his_last_game10_"+next_num);
                    var img = getHeroHeadById(v.HeroID1);
                    $("#his_last_game10_"+num+" .his_headimg").attr("src", img);
                    $("#his_last_game10_"+num+" .pvplevel").text("LV."+v.PvpLevel);
                    if(v.GameResult == 1){
                        $("#his_last_game10_"+num+" .his_info_m_txt").removeClass("_faltxt").addClass("_suctxt").text("ʤ��");
                    }else{
                        $("#his_last_game10_"+num+" .his_info_m_txt").removeClass("_suctxt").addClass("_faltxt").text("ʧ��");
                    }
                    // �Ծ�ģʽ
                    $("#his_last_game10_"+num+" .his_info_m_maptxt").text(v.GameTypeName);
                    $("#his_last_game10_"+num+" .gameduration").text(Math.round(parseInt(v.UsedTime)/60));
                    var kda = v.KDA;
					if(v.GradeOfRank < 1) v.GradeOfRank = 1;
                    var grade_level_url = getRankImgByGradeLevel(v.GradeOfRank);
                    $("#his_last_game10_"+num+" .his_info_dan").attr("src", grade_level_url);
                    
                    // todo deal
                    $(".hisdata").eq(num).css({"background":"url("+hisImg_url+")","background-position":"0px "+num*(-30)+"px"});
                    
//                    $("#his_last_game10_"+num+" .info_kda").text(" KDA:"+kda.toFixed(1));
//                    $("#his_last_game10_"+num+" .killnum").text(v.KillCnt);
//                    $("#his_last_game10_"+num+" .deathnum").text(v.DeadCnt);
//                    $("#his_last_game10_"+num+" .assistnum").text(v.AssistCnt);
                    
                    $("#his_last_game10_"+num+" .equipment_time").text(v.GameSeqDateTime);
                    // ���ճ�װ
                    var equip_str = v.FinalInBattleEquipStr.split(",");
                    var equip_str_html = '';
                    if(equip_str.length > 0){
                        $.each(equip_str, function(kkk, vvv){
                            vvv = vvv.split("+");
                            if(vvv[0] > 0){
                                var equip_url = getEquipById(vvv[0]);
                                equip_str_html += '<img width="50" height="50" src="'+equip_url+'">';
                            }
                        });
                    }
                    $("#his_last_game10_"+num+" .equipment_imglist").html(equip_str_html);
                    // ����
                    $("#his_last_game10_"+num+" .mvp_num").text(v.score);
                    // �Ƿ�MVP
                    if(v.MvpCnt == 1){
                        $("#his_last_game10_"+num+" .his_info_mvp").show();
                    }else{
                        $("#his_last_game10_"+num+" .his_info_mvp").hide();
                    }

                    $("#his_last_game10_"+num).show();
                });
                
            }
        });
    }

    function IDE_GetHisRecord() {
        IDE_GetHeadInfo(1);

        IDE.emit({
            actId: "5_VaG4AS",
            token: "5X8ASi",
            loading: true, // ����loading����,Ĭ�ϲ�����
            sData: { sArea: area, sPlatId: [2, 4].indexOf(+area) ? 0 : 1, sPartition: partition },
            openToOpen: { sAMSTrusteeship: 1, ams_targetappid_wx: game_wx_appid, ams_targetappid_qc: game_qq_appid },
            success: function (result) {
                console.log("�ɹ���ȡ��ʷս��", result);
                // ������Ϣ
                if(result.data.user != null) {
                    var user = result.data.user;
                    $(".level-ico").text(user.pvplevel);
                    var grade_level = +user.grade_level || 1;
                    if(grade_level < 1) grade_level = 1; // ���û�����λ��ʹ����ͭIIIͼƬ
                    $(".grade_level").text(getRankingStarText(user.ranking_star))//rankInfo[String(grade_level)]);
                }
                // ��ʷս��
                if(result.data.history && result.data.history.length > 0)
                {
                    var history = result.data.history;
                    // ���һ�α���
                    var his_last1 = history[0];
                    var his_last10 = history;

                    var his_info = 0+"|"+his_last1.GameSeq+"|"+his_last1.GameSvrEntity+"|"+his_last1.RelaySvrEntity+"|"+his_last1.LineType+"|"+his_last1.Camp1Num;
                    $("#his_last_linfo1").find(".his_info_arrow").attr("data-id", his_info);
                    var img = getHeroHeadById(his_last1.HeroID1);
                    $("#his_last_linfo1 .his_headimg").attr("src", img);
                    $("#his_last_linfo1 .pvplevel").text("LV."+his_last1.PvpLevel);
                    if(his_last1.GameResult == 1){
                        $("#his_last_linfo1 .his_info_m_txt").removeClass("_faltxt").addClass("_suctxt").text("ʤ��");
                    }else{
                        $("#his_last_linfo1 .his_info_m_txt").removeClass("_suctxt").addClass("_faltxt").text("ʧ��");
                    }
                    // �Ծ�ģʽ
                    $("#his_last_linfo1 .his_info_m_maptxt").text(his_last1.GameTypeName);

                    $("#his_last_linfo1 .gameduration").text(Math.floor(parseInt(his_last1.UsedTime)/60)+':'+(parseInt(his_last1.UsedTime)%60 == 0?'00':(parseInt(his_last1.UsedTime)%60 < 10?('0'+(parseInt(his_last1.UsedTime)%60)):parseInt(his_last1.UsedTime)%60)));
                    var kda = his_last1.KDA;
                    if(his_last1.GradeOfRank < 1) his_last1.GradeOfRank = 1;
                    var grade_level_url = getRankImgByGradeLevel(his_last1.GradeOfRank);
                    $("#his_last_linfo1 .his_info_dan").attr("src", grade_level_url);
                    
                    // ��߷���  todo deal
                    var hisImg_url = curpro+"//mapps.game.qq.com/yxzj/web201605/getHistoryImg.php?appid="+appid+"&area="+area+"&partition="+partition +"&r="+Math.random();
                    var sPlatId = [2, 4].indexOf(+area) ? 0 : 1
                    var openid = milo.cookie.get("openid");
                    //var hisImg_url = "https://comm.ams.game.qq.com/ide/?instanceid=483875&sIdeFlow=idFMJq&sOpenId="+openid+"&sArea="+area+"&sPlatId="+sPlatId+"&sPartition="+partition +"&r="+Math.random();
                    //$(".hisdata").eq(0).css("background","url("+hisImg_url+")");

                    IDE_GetHistoryImg();
                    var gameSeqDate = Date.parse(his_last1.dtEventTime)/1000 - parseInt(his_last1.UsedTime)
                    var gameSeqDateTime = new Date(gameSeqDate*1000);
                    var y = gameSeqDateTime.getFullYear();
                    var m = (gameSeqDateTime.getMonth()+1) < 10 ? '0' + (gameSeqDateTime.getMonth()+1) : (gameSeqDateTime.getMonth()+1);
                    var d = gameSeqDateTime.getDate() <10?'0'+gameSeqDateTime.getDate():gameSeqDateTime.getDate();
                    var h = gameSeqDateTime.getHours()<10?'0'+gameSeqDateTime.getHours():gameSeqDateTime.getHours();
                    var mm = gameSeqDateTime.getMinutes()<10?'0'+gameSeqDateTime.getMinutes():gameSeqDateTime.getMinutes();
                    var s = gameSeqDateTime.getSeconds()<10?'0'+gameSeqDateTime.getSeconds():gameSeqDateTime.getSeconds();

                    $("#his_last_linfo1 .equipment_time").text(y+'-'+m+'-'+d+' '+h+':'+mm+':'+s);
                    // ���ճ�װ
                    var equip_str = his_last1.FinalInBattleEquipStr.split(",");
                    var equip_str_html = '';
                    if(equip_str.length > 0){
                        $.each(equip_str, function(k, v){
                            v = v.split("+");
                            if(v[0] > 0){
                                var equip_url = getEquipById(v[0]);
                                equip_str_html += '<img width="50" height="50" src="'+equip_url+'">';
                            }
                        });
                    }
                    $("#his_last_linfo1 .equipment_imglist").html(equip_str_html);
                    // ����
                    $("#his_last_linfo1 .mvp_num").text(his_last1.score);
                    // �Ƿ�MVP
                    if(his_last1.MvpCnt == 1){
                        $("#his_last_linfo1 .his_info_mvp").show();
                    }else{
                        $("#his_last_linfo1 .his_info_mvp").hide();
                    }

                    $("#his_last_linfo1").show();

                    // ��ʷս��
                    var num = '';
                    $.each(his_last10, function(k, v){
                        if(k == 0){
                            return;
                        }
                        num = k;
                        next_num = num + 1;
                        var obj = $("#his_last_game10_"+num).clone(true);
                        obj.attr("id", "his_last_game10_"+next_num);

                        obj.insertAfter("#his_lastgame_detail_"+num);

                        var his_info = num+"|"+v.GameSeq+"|"+v.GameSvrEntity+"|"+v.RelaySvrEntity+"|"+v.LineType+"|"+v.Camp1Num;
                        $("#his_last_game10_"+num).find(".his_info_arrow").attr("data-id", his_info);

                        var obj_detail = $("#his_lastgame_detail_"+num).clone(true);
                        obj_detail.attr("id", "his_lastgame_detail_"+next_num);
                        obj_detail.find(".item_succ_i").attr("id", "item_i_succ_"+next_num+"_"+1);
                        obj_detail.find(".item_fail_i").attr("id", "item_i_fail_"+next_num+"_"+1);
                        obj_detail.insertAfter("#his_last_game10_"+next_num);
                        var img = getHeroHeadById(v.HeroID1);
                        $("#his_last_game10_"+num+" .his_headimg").attr("src", img);
                        $("#his_last_game10_"+num+" .pvplevel").text("LV."+v.PvpLevel);
                        if(v.GameResult == 1){
                            $("#his_last_game10_"+num+" .his_info_m_txt").removeClass("_faltxt").addClass("_suctxt").text("ʤ��");
                        }else{
                            $("#his_last_game10_"+num+" .his_info_m_txt").removeClass("_suctxt").addClass("_faltxt").text("ʧ��");
                        }
                        // �Ծ�ģʽ
                        $("#his_last_game10_"+num+" .his_info_m_maptxt").text(v.GameTypeName);
                        $("#his_last_game10_"+num+" .gameduration").text(Math.floor(parseInt(v.UsedTime)/60)+':'+(parseInt(v.UsedTime)%60 == 0?'00':(parseInt(v.UsedTime)%60 < 10?('0'+(parseInt(v.UsedTime)%60)):parseInt(v.UsedTime)%60)));
                        var kda = v.KDA;
                        if(v.GradeOfRank < 1) v.GradeOfRank = 1;
                        var grade_level_url = getRankImgByGradeLevel(v.GradeOfRank);
                        $("#his_last_game10_"+num+" .his_info_dan").attr("src", grade_level_url);
                        
                        // todo deal
                        gameSeqDate = Date.parse(v.dtEventTime)/1000 - parseInt(v.UsedTime)
                        gameSeqDateTime = new Date(gameSeqDate*1000);
                        y = gameSeqDateTime.getFullYear();
                        m = (gameSeqDateTime.getMonth()+1) < 10 ? '0' + (gameSeqDateTime.getMonth()+1) : (gameSeqDateTime.getMonth()+1);
                        d = gameSeqDateTime.getDate() <10?'0'+gameSeqDateTime.getDate():gameSeqDateTime.getDate();
                        h = gameSeqDateTime.getHours()<10?'0'+gameSeqDateTime.getHours():gameSeqDateTime.getHours();
                        mm = gameSeqDateTime.getMinutes()<10?'0'+gameSeqDateTime.getMinutes():gameSeqDateTime.getMinutes();
                        s = gameSeqDateTime.getSeconds()<10?'0'+gameSeqDateTime.getSeconds():gameSeqDateTime.getSeconds();
                        $("#his_last_game10_"+num+" .equipment_time").text(y+'-'+m+'-'+d+' '+h+':'+mm+':'+s);
                        // ���ճ�װ
                        var equip_str = v.FinalInBattleEquipStr.split(",");
                        var equip_str_html = '';
                        if(equip_str.length > 0){
                            $.each(equip_str, function(kkk, vvv){
                                vvv = vvv.split("+");
                                if(vvv[0] > 0){
                                    var equip_url = getEquipById(vvv[0]);
                                    equip_str_html += '<img width="50" height="50" src="'+equip_url+'">';
                                }
                            });
                        }
                        $("#his_last_game10_"+num+" .equipment_imglist").html(equip_str_html);
                        // ����
                        $("#his_last_game10_"+num+" .mvp_num").text(v.score);
                        // �Ƿ�MVP
                        if(v.MvpCnt == 1){
                            $("#his_last_game10_"+num+" .his_info_mvp").show();
                        }else{
                            $("#his_last_game10_"+num+" .his_info_mvp").hide();
                        }
                        $("#his_last_game10_"+num).show();
                    });
                    
                }
            },
            fail: function (result) {
                console.error("�û���Ϣ��ȡʧ��", result);
                if (result.iRet === 101 || result.iRet === "101") {
                    // todo ��¼̬ʧЧ����Ҫ���µ���¼���� ����������ʵ�֣�
                    alert("�����µ�¼��");
                    TGDialogS("login_select");
                } else {
                    alert("ϵͳ��æ�����Ժ�����");
                    // alert("����ʧ�ܣ�" + res.sMsg);
                }
            }
        });
    }


    function IDE_GetHistoryImg(){
        IDE.emit({
            actId: '5_VaG4AS',
            token: 'idFMJq',
            loading: true, // ����loading����,Ĭ�ϲ�����
            sData: { sArea: area, sPlatId: [2, 4].indexOf(+area) ? 0 : 1, sPartition: partition},
            openToOpen: { sAMSTrusteeship: 1, ams_targetappid_wx: game_wx_appid, ams_targetappid_qc: game_qq_appid },
            success: function (res) {
                console.log(res);
                for(var num in res.data.imagejpegs){
                    $(".hisdata").eq(num).attr('src',res.data.imagejpegs[num]);
                }
                //$(".hisdata").attr('src',res.data.imagejpegs[0]);
                //$(".hisdata").eq(num).css({"background":"url("+hisImg_url+")","background-position":"0px "+num*(-30)+"px"});
                // $(".hisdata_first").css('background-image','url('+res.data.imagejpeg+')')
            },
            fail: function (res) {
                if(res.iRet === 101 || res.iRet === '101'){
                    //todo ��¼̬ʧЧ����Ҫ���µ���¼���� ����������ʵ�֣�
                } else if (res.iRet === 99998 || res.iRet === '99998') {
                    // todo �����ύ�󶨴�������
                }
                console.log(res);
            }
        });
    }

    function IDE_GetHisRecordDetail(id, gameseq, gamesvrentity, relaysvrentity, linetype, teamnum){
        var flow_142272 = {
            actId: '5_VaG4AS',
            token: 'rKzZpe',
            loading: true, // ����loading����,Ĭ�ϲ�����
            sData: {
                sArea: area,
                sPlatId: [2, 4].indexOf(+area) ? 0 : 1,
                sPartition: partition,
                gameseq: gameseq, // gameseq
                gamesvrentity: gamesvrentity, // gamesvrentity
                relaysvrentity: relaysvrentity, // relaysvrentity
                linetype: linetype, // linetype
                teamnum: teamnum, // teamnum
            },
            success: function (result) {
                console.log(result);


                if(typeof(result) == "undefined")
                {
                    alert("ϵͳ��æ�����Ժ�����");
                    return;
                }
                // console.log(loaded);
                if(result.iRet != 0)
                {
                    alert(result.sMsg);
                    return;
                }

                if(typeof(result.data.his_record_detail) != "undefined")
                {
                    // ��־�Ѽ���
                    $("#his_lastgame_detail_"+id).attr("data-id", "1");

                    // console.log(result.data.his_record_detail);
                    his_record_detail = result.data.his_record_detail;
                    his_record_detail_alldata = result.data.his_record_detail_alldata;

                    // todo test �ÿ�

                    var succ_num = 1;
                    var fail_num = 1;

                    var snum = 0;
                    var fnum = 5;

                    var detail_url = curpro+"//mapps.game.qq.com/yxzj/web201605/getHistoryDetailImg.php?appid="+appid+"&area="+area+"&partition="+partition +"&gameseq=" + gameseq + "&gamesvrentity=" + gamesvrentity + "&relaysvrentity=" + relaysvrentity + "&linetype=" + linetype + "&teamnum=" + teamnum + "&r="+Math.random();;
                    $.each(his_record_detail, function(k,v){

                        if(v.GameResult == 1){  // ʤ����
                            next_succ_num = succ_num+1;
                            var obj = $("#item_i_succ_"+id+"_"+succ_num).clone(true);
                            obj.attr("id", "item_i_succ_"+id+"_"+next_succ_num);
                            obj.insertAfter("#item_i_succ_"+id+"_"+succ_num);
                            var hero_img = getHeroHeadById(v.HeroID1);
                            $("#item_i_succ_"+id+"_"+succ_num+" .item_herohead").attr("src", hero_img);
                            // �������
                            $("#item_i_succ_"+id+"_"+succ_num+" .item_name").text(decodeURIComponent(v.AcntName));

                            // todo ͼƬ������
                            $("#item_i_succ_"+id+"_"+succ_num+" .hisDetail").css({"background":"url("+detail_url+")","background-position":"-700px -"+snum*(50)+"px"});
//                        $("#his_lastgame_detail_"+id+" .hisDetail").eq(pos).css({"background":"url(//mapps.game.qq.com/yxzj/web201605/getHistoryDetailImg.php)","background-position":"-700px "+pos*(50)+"px"});
//                        $("#item_i_succ_"+id+"_"+succ_num+" .item_money").text("��Ǯ��"+v.TotalInBattleCoin);
//                        $("#item_i_succ_"+id+"_"+succ_num+" .killnum").text(v.KillCnt+"ɱ");
//                        $("#item_i_succ_"+id+"_"+succ_num+" .deathnum").text(v.DeadCnt+"��");
//                        $("#item_i_succ_"+id+"_"+succ_num+" .assistnum").text(v.AssistCnt+"����");
//
                            // ���ճ�װ
                            var equip_str = v.FinalInBattleEquipStr.split(",");
                            var equip_str_html = '';
                            if(equip_str.length > 0){
                                $.each(equip_str, function(kkk, vvv){
                                    vvv = vvv.split("+");
                                    if(vvv[0] > 0){
                                        var equip_url = getEquipById(vvv[0]);
                                        equip_str_html += '<img width="50" height="50" src="' + equip_url + '">';
                                    }
                                });
                            }
                            // MVP����
                            if(v.MvpCnt > 0){
                                $("#item_i_succ_"+id+"_"+succ_num+" .icon_inMVP").html('<img class="his_info_mvp" width="70" height="64" src="//game.gtimg.cn/images/yxzj/web201605/page/icon_MVP2.png"><span class="mvp_innum">"+v.MvpScore+"</span>');
                            }else{
                                $("#item_i_succ_"+id+"_"+succ_num+" .icon_inMVP").html('<img class="his_info_mvp" width="70" height="64" src="//game.gtimg.cn/images/yxzj/web201605/page/icon_MVP3.png"><span class="mvp_innum _innormal">"+v.MvpScore+"</span>');
                            }
                            $("#item_i_succ_"+id+"_"+succ_num+" .item_equipment").html(equip_str_html);

                            // Сͼ��
                            var his_info_r_attr_html = '';
                            for(i=1;i<=8;i++){
                                if(v["act0"+i] == 1){
                                    his_info_r_attr_html += '<i class="r_attr _at0"+i+""></i>';
                                }
                            }
                            if(v["at_3kill"] == 1){  // ��ɱ
                                his_info_r_attr_html += '<i class="r_attr _at_3kill"></i>';
                            }
                            if(v["at_4kill"] == 1){  // ��ɱ
                                his_info_r_attr_html += '<i class="r_attr _at_4kill"></i>';
                            }
                            if(v["at_5kill"] == 1){  // ��ɱ
                                his_info_r_attr_html += '<i class="r_attr _at_5kill"></i>';
                            }
                            $("#item_i_succ_"+id+"_"+succ_num+" .his_info_r_attr").html(his_info_r_attr_html);

                            // ����
//                        var alldata = his_record_detail_alldata[v.GameResult];
                            var hero_img = getHeroHeadById(v.HeroID1);
                            $("#item_i_succ_"+id+"_"+succ_num+" .his_roleimg").attr("src", hero_img);

                            // todo ͼ�񻯴���  ʤ����
                            $("#item_i_succ_"+id+"_"+succ_num+" .hisDetailRate").css({"background":"url("+detail_url+")","background-position":"0px -"+snum*(50)+"px"});

//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_money p:eq(0)").text("��ý�Ǯ��"+v.TotalInBattleCoin);
//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_allout p:eq(0)").text("�������"+v.TotalHurtCnt);
//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_allout p:eq(1)").text("������ٷֱȣ�"+Math.round((v.TotalHurtCnt/alldata.TotalHurtCnt)*100)+"%");
//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_tohurt p:eq(0)").text("��Ӣ���˺���"+v.TotalHurtHeroCnt);
//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_tohurt p:eq(1)").text("��Ӣ���˺��ٷֱȣ�"+Math.round((v.TotalHurtHeroCnt/alldata.TotalHurtHeroCnt)*100)+"%");
//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_hurt p:eq(0)").text("�����˺���"+v.TotalBeHurtCnt);
//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_hurt p:eq(1)").text("�����˺��ٷֱȣ�"+Math.round((v.TotalBeHurtCnt/alldata.TotalBeHurtCnt)*100)+"%");


                            $("#item_i_succ_"+id+"_"+succ_num).show();

                            succ_num++;
                            snum ++;
                        }else{  // ʧ�ܷ�
                            next_fail_num = fail_num+1;
                            var obj = $("#item_i_fail_"+id+"_"+fail_num).clone(true);
                            obj.attr("id", "item_i_fail_"+id+"_"+next_fail_num);

                            obj.insertAfter("#item_i_fail_"+id+"_"+fail_num);
                            var hero_img = getHeroHeadById(v.HeroID1);
                            $("#item_i_fail_"+id+"_"+fail_num+" .item_herohead").attr("src", hero_img);
                            // �������
                            $("#item_i_fail_"+id+"_"+fail_num+" .item_name").text(decodeURIComponent(v.AcntName));

                            // todo ͼ�񻯴���  ʤ����
                            $("#item_i_fail_"+id+"_"+fail_num+" .hisDetail").css({"background":"url("+detail_url+")","background-position":"-700px -"+fnum*(50)+"px"});
//                        $("#item_i_fail_"+id+"_"+fail_num+" .item_money").text("��Ǯ��"+v.TotalInBattleCoin);
//                        $("#item_i_fail_"+id+"_"+fail_num+" .killnum").text(v.KillCnt+"ɱ");
//                        $("#item_i_fail_"+id+"_"+fail_num+" .deathnum").text(v.DeadCnt+"��");
//                        $("#item_i_fail_"+id+"_"+fail_num+" .assistnum").text(v.AssistCnt+"����");
                            // ���ճ�װ
                            var equip_str = v.FinalInBattleEquipStr.split(",");
                            var equip_str_html = '';
                            if(equip_str.length > 0){
                                $.each(equip_str, function(kkk, vvv){
                                    vvv = vvv.split("+");
                                    if(vvv[0] > 0){
                                        var equip_url = getEquipById(vvv[0]);
                                        equip_str_html += '<img width="50" height="50" src=""+equip_url+"">';
                                    }
                                });
                            }
                            // MVP����
                            if(v.LoseMvp > 0){
                                $("#item_i_fail_"+id+"_"+fail_num+" .icon_inMVP").html('<img class="his_info_mvp" width="70" height="64" src="//game.gtimg.cn/images/yxzj/web201605/page/icon_MVP2.png"><span class="mvp_innum">"+v.MvpScore+"</span>');
                            }else{
                                $("#item_i_fail_"+id+"_"+fail_num+" .icon_inMVP").html('<img class="his_info_mvp" width="70" height="64" src="//game.gtimg.cn/images/yxzj/web201605/page/icon_MVP3.png"><span class="mvp_innum _innormal">"+v.MvpScore+"</span>');
                            }
                            $("#item_i_fail_"+id+"_"+fail_num+" .item_equipment").html(equip_str_html);

                            // Сͼ��
                            var his_info_r_attr_html = '';
                            for(i=1;i<=8;i++){
                                if(v["act0"+i] == 1){
                                    his_info_r_attr_html += '<i class="r_attr _at0"+i+""></i>';
                                }
                            }
                            if(v["at_3kill"] == 1){  // ��ɱ
                                his_info_r_attr_html += '<i class="r_attr _at_3kill"></i>';
                            }
                            if(v["at_4kill"] == 1){  // ��ɱ
                                his_info_r_attr_html += '<i class="r_attr _at_4kill"></i>';
                            }
                            if(v["at_5kill"] == 1){  // ��ɱ
                                his_info_r_attr_html += '<i class="r_attr _at_5kill"></i>';
                            }
                            $("#item_i_fail_"+id+"_"+fail_num+" .his_info_r_attr").html(his_info_r_attr_html);

                            // ����
//                        var alldata = his_record_detail_alldata[v.GameResult];
                            var hero_img = getHeroHeadById(v.HeroID1);
                            $("#item_i_fail_"+id+"_"+fail_num+" .his_roleimg").attr("src", hero_img);

                            // todo ͼ�񻯴���  ʤ����
                            $("#item_i_fail_"+id+"_"+fail_num+" .hisDetailRate").css({"background":"url("+detail_url+")","background-position":"0px -"+fnum*(50)+"px"});

//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_money p:eq(0)").text("��ý�Ǯ��"+v.TotalInBattleCoin);
//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_allout p:eq(0)").text("�������"+v.TotalHurtCnt);
//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_allout p:eq(1)").text("������ٷֱȣ�"+Math.round((v.TotalHurtCnt/alldata.TotalHurtCnt)*100)+"%");
//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_tohurt p:eq(0)").text("��Ӣ���˺���"+v.TotalHurtHeroCnt);
//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_tohurt p:eq(1)").text("��Ӣ���˺��ٷֱȣ�"+Math.round((v.TotalHurtHeroCnt/alldata.TotalHurtHeroCnt)*100)+"%");
//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_hurt p:eq(0)").text("�����˺���"+v.TotalBeHurtCnt);
//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_hurt p:eq(1)").text("�����˺��ٷֱȣ�"+Math.round((v.TotalBeHurtCnt/alldata.TotalBeHurtCnt)*100)+"%");

                            $("#item_i_fail_"+id+"_"+fail_num).show();

                            fail_num++;
                            fnum ++;
                        }



                        $(".item_i").hover(function(){
                            $(this).find(".his_detailcont").show();
                        },function(){
                            $(this).find(".his_detailcont").hide();
                        });
                    });

                }

            },
            fail: function (res) {
                if(res.iRet === 101 || res.iRet === '101'){
                    //todo ��¼̬ʧЧ����Ҫ���µ���¼���� ����������ʵ�֣�
                } else if (res.iRet === 99998 || res.iRet === '99998') {
                    // todo �����ύ�󶨴�������
                }
                console.log(res);
            }
        }

        IDE.emit(flow_142272);
    }

    // ��ʷս����ϸ
    function GetHisRecordDetail(id, gameseq, gamesvrentity, relaysvrentity, linetype, teamnum)
    {
        var url = curpro+"//mapps.game.qq.com/yxzj/web201605/GetHisRecordDetail.php?appid="+appid+"&area="+area+"&partition="+partition + "&roleid=" + roleid + "&gameseq=" + gameseq + "&gamesvrentity=" + gamesvrentity + "&relaysvrentity=" + relaysvrentity + "&linetype=" + linetype + "&teamnum=" + teamnum + "&r="+Math.random();
        include(url, function(loaded){
            if(!loaded || typeof(result) == "undefined")
            {
                alert("ϵͳ��æ�����Ժ�����");
                return;
            }
            // console.log(loaded);
            if(result.iRet != 0)
            {
                alert(result.sMsg);
                return;
            }

            if(typeof(result.data.his_record_detail) != "undefined")
            {
                // ��־�Ѽ���
                $("#his_lastgame_detail_"+id).attr("data-id", "1");

                // console.log(result.data.his_record_detail);
                his_record_detail = result.data.his_record_detail;
                his_record_detail_alldata = result.data.his_record_detail_alldata;

                // todo test �ÿ�

                var succ_num = 1;
                var fail_num = 1;
                
                var snum = 0;
                var fnum = 5;
                
                var detail_url = curpro+"//mapps.game.qq.com/yxzj/web201605/getHistoryDetailImg.php?appid="+appid+"&area="+area+"&partition="+partition +"&gameseq=" + gameseq + "&gamesvrentity=" + gamesvrentity + "&relaysvrentity=" + relaysvrentity + "&linetype=" + linetype + "&teamnum=" + teamnum + "&r="+Math.random();;
                $.each(his_record_detail, function(k,v){
                    
                    if(v.GameResult == 1){  // ʤ����
                        next_succ_num = succ_num+1;
                        var obj = $("#item_i_succ_"+id+"_"+succ_num).clone(true);
                        obj.attr("id", "item_i_succ_"+id+"_"+next_succ_num);
                        obj.insertAfter("#item_i_succ_"+id+"_"+succ_num);
                        var hero_img = getHeroHeadById(v.HeroID1);
                        $("#item_i_succ_"+id+"_"+succ_num+" .item_herohead").attr("src", hero_img);
                        // �������
                        $("#item_i_succ_"+id+"_"+succ_num+" .item_name").text(decodeURIComponent(v.AcntName));

                        // todo ͼƬ������
                        $("#item_i_succ_"+id+"_"+succ_num+" .hisDetail").css({"background":"url("+detail_url+")","background-position":"-700px -"+snum*(50)+"px"});
//                        $("#his_lastgame_detail_"+id+" .hisDetail").eq(pos).css({"background":"url(//mapps.game.qq.com/yxzj/web201605/getHistoryDetailImg.php)","background-position":"-700px "+pos*(50)+"px"});
//                        $("#item_i_succ_"+id+"_"+succ_num+" .item_money").text("��Ǯ��"+v.TotalInBattleCoin);
//                        $("#item_i_succ_"+id+"_"+succ_num+" .killnum").text(v.KillCnt+"ɱ");
//                        $("#item_i_succ_"+id+"_"+succ_num+" .deathnum").text(v.DeadCnt+"��");
//                        $("#item_i_succ_"+id+"_"+succ_num+" .assistnum").text(v.AssistCnt+"����");
//                        
                        // ���ճ�װ
                        var equip_str = v.FinalInBattleEquipStr.split(",");
                        var equip_str_html = '';
                        if(equip_str.length > 0){
                            $.each(equip_str, function(kkk, vvv){
                                vvv = vvv.split("+");
                                if(vvv[0] > 0){
                                    var equip_url = getEquipById(vvv[0]);
                                    equip_str_html += '<img width="50" height="50" src="' + equip_url + '">';
                                }
                            });
                        }
                        // MVP����
                        if(v.MvpCnt > 0){
                            $("#item_i_succ_"+id+"_"+succ_num+" .icon_inMVP").html('<img class="his_info_mvp" width="70" height="64" src="//game.gtimg.cn/images/yxzj/web201605/page/icon_MVP2.png"><span class="mvp_innum">"+v.MvpScore+"</span>');
                        }else{
                            $("#item_i_succ_"+id+"_"+succ_num+" .icon_inMVP").html('<img class="his_info_mvp" width="70" height="64" src="//game.gtimg.cn/images/yxzj/web201605/page/icon_MVP3.png"><span class="mvp_innum _innormal">"+v.MvpScore+"</span>');
                        }
                        $("#item_i_succ_"+id+"_"+succ_num+" .item_equipment").html(equip_str_html);

                        // Сͼ��
                        var his_info_r_attr_html = '';
                        for(i=1;i<=8;i++){
                            if(v["act0"+i] == 1){
                                his_info_r_attr_html += '<i class="r_attr _at0"+i+""></i>';
                            }
                        }
                        if(v["at_3kill"] == 1){  // ��ɱ
                            his_info_r_attr_html += '<i class="r_attr _at_3kill"></i>';
                        }
                        if(v["at_4kill"] == 1){  // ��ɱ
                            his_info_r_attr_html += '<i class="r_attr _at_4kill"></i>';
                        }
                        if(v["at_5kill"] == 1){  // ��ɱ
                            his_info_r_attr_html += '<i class="r_attr _at_5kill"></i>';
                        }
                        $("#item_i_succ_"+id+"_"+succ_num+" .his_info_r_attr").html(his_info_r_attr_html);

                        // ����
//                        var alldata = his_record_detail_alldata[v.GameResult];
                        var hero_img = getHeroHeadById(v.HeroID1);
                        $("#item_i_succ_"+id+"_"+succ_num+" .his_roleimg").attr("src", hero_img);

                        // todo ͼ�񻯴���  ʤ����
                        $("#item_i_succ_"+id+"_"+succ_num+" .hisDetailRate").css({"background":"url("+detail_url+")","background-position":"0px -"+snum*(50)+"px"});

//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_money p:eq(0)").text("��ý�Ǯ��"+v.TotalInBattleCoin);
//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_allout p:eq(0)").text("�������"+v.TotalHurtCnt);
//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_allout p:eq(1)").text("������ٷֱȣ�"+Math.round((v.TotalHurtCnt/alldata.TotalHurtCnt)*100)+"%");
//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_tohurt p:eq(0)").text("��Ӣ���˺���"+v.TotalHurtHeroCnt);
//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_tohurt p:eq(1)").text("��Ӣ���˺��ٷֱȣ�"+Math.round((v.TotalHurtHeroCnt/alldata.TotalHurtHeroCnt)*100)+"%");
//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_hurt p:eq(0)").text("�����˺���"+v.TotalBeHurtCnt);
//                        $("#item_i_succ_"+id+"_"+succ_num+" .his_role_hurt p:eq(1)").text("�����˺��ٷֱȣ�"+Math.round((v.TotalBeHurtCnt/alldata.TotalBeHurtCnt)*100)+"%");


                        $("#item_i_succ_"+id+"_"+succ_num).show();

                        succ_num++;
                        snum ++;
                    }else{  // ʧ�ܷ�
                        next_fail_num = fail_num+1;
                        var obj = $("#item_i_fail_"+id+"_"+fail_num).clone(true);
                        obj.attr("id", "item_i_fail_"+id+"_"+next_fail_num);

                        obj.insertAfter("#item_i_fail_"+id+"_"+fail_num);
                        var hero_img = getHeroHeadById(v.HeroID1);
                        $("#item_i_fail_"+id+"_"+fail_num+" .item_herohead").attr("src", hero_img);
                        // �������
                        $("#item_i_fail_"+id+"_"+fail_num+" .item_name").text(decodeURIComponent(v.AcntName));
                        
                        // todo ͼ�񻯴���  ʤ����
                        $("#item_i_fail_"+id+"_"+fail_num+" .hisDetail").css({"background":"url("+detail_url+")","background-position":"-700px -"+fnum*(50)+"px"});
//                        $("#item_i_fail_"+id+"_"+fail_num+" .item_money").text("��Ǯ��"+v.TotalInBattleCoin);
//                        $("#item_i_fail_"+id+"_"+fail_num+" .killnum").text(v.KillCnt+"ɱ");
//                        $("#item_i_fail_"+id+"_"+fail_num+" .deathnum").text(v.DeadCnt+"��");
//                        $("#item_i_fail_"+id+"_"+fail_num+" .assistnum").text(v.AssistCnt+"����");
                        // ���ճ�װ
                        var equip_str = v.FinalInBattleEquipStr.split(",");
                        var equip_str_html = '';
                        if(equip_str.length > 0){
                            $.each(equip_str, function(kkk, vvv){
                                vvv = vvv.split("+");
                                if(vvv[0] > 0){
                                    var equip_url = getEquipById(vvv[0]);
                                    equip_str_html += '<img width="50" height="50" src=""+equip_url+"">';
                                }
                            });
                        }
                        // MVP����
                        if(v.LoseMvp > 0){
                            $("#item_i_fail_"+id+"_"+fail_num+" .icon_inMVP").html('<img class="his_info_mvp" width="70" height="64" src="//game.gtimg.cn/images/yxzj/web201605/page/icon_MVP2.png"><span class="mvp_innum">"+v.MvpScore+"</span>');
                        }else{
                            $("#item_i_fail_"+id+"_"+fail_num+" .icon_inMVP").html('<img class="his_info_mvp" width="70" height="64" src="//game.gtimg.cn/images/yxzj/web201605/page/icon_MVP3.png"><span class="mvp_innum _innormal">"+v.MvpScore+"</span>');
                        }
                        $("#item_i_fail_"+id+"_"+fail_num+" .item_equipment").html(equip_str_html);

                        // Сͼ��
                        var his_info_r_attr_html = '';
                        for(i=1;i<=8;i++){
                            if(v["act0"+i] == 1){
                                his_info_r_attr_html += '<i class="r_attr _at0"+i+""></i>';
                            }
                        }
                        if(v["at_3kill"] == 1){  // ��ɱ
                            his_info_r_attr_html += '<i class="r_attr _at_3kill"></i>';
                        }
                        if(v["at_4kill"] == 1){  // ��ɱ
                            his_info_r_attr_html += '<i class="r_attr _at_4kill"></i>';
                        }
                        if(v["at_5kill"] == 1){  // ��ɱ
                            his_info_r_attr_html += '<i class="r_attr _at_5kill"></i>';
                        }
                        $("#item_i_fail_"+id+"_"+fail_num+" .his_info_r_attr").html(his_info_r_attr_html);

                        // ����
//                        var alldata = his_record_detail_alldata[v.GameResult];
                        var hero_img = getHeroHeadById(v.HeroID1);
                        $("#item_i_fail_"+id+"_"+fail_num+" .his_roleimg").attr("src", hero_img);
                        
                        // todo ͼ�񻯴���  ʤ����
                        $("#item_i_fail_"+id+"_"+fail_num+" .hisDetailRate").css({"background":"url("+detail_url+")","background-position":"0px -"+fnum*(50)+"px"});

//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_money p:eq(0)").text("��ý�Ǯ��"+v.TotalInBattleCoin);
//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_allout p:eq(0)").text("�������"+v.TotalHurtCnt);
//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_allout p:eq(1)").text("������ٷֱȣ�"+Math.round((v.TotalHurtCnt/alldata.TotalHurtCnt)*100)+"%");
//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_tohurt p:eq(0)").text("��Ӣ���˺���"+v.TotalHurtHeroCnt);
//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_tohurt p:eq(1)").text("��Ӣ���˺��ٷֱȣ�"+Math.round((v.TotalHurtHeroCnt/alldata.TotalHurtHeroCnt)*100)+"%");
//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_hurt p:eq(0)").text("�����˺���"+v.TotalBeHurtCnt);
//                        $("#item_i_fail_"+id+"_"+fail_num+" .his_role_hurt p:eq(1)").text("�����˺��ٷֱȣ�"+Math.round((v.TotalBeHurtCnt/alldata.TotalBeHurtCnt)*100)+"%");

                        $("#item_i_fail_"+id+"_"+fail_num).show();

                        fail_num++;
                        fnum ++;
                    }
                    
                    

                    $(".item_i").hover(function(){
                        $(this).find(".his_detailcont").show();
                    },function(){
                        $(this).find(".his_detailcont").hide();
                    });
                });
                
            }
        });
    }

    var lastgame_arrow=$(".his_info_arrow");
    function showRecord(_this,id){
        id = id.split("|");

        if(id.length == 6){
            var gameseq = id[1];
            var gamesvrentity = id[2];
            var relaysvrentity = id[3];
            var linetype = id[4];
            var teamnumm = id[5];
            id = id[0];
        }else{
            return false;
        }

        if($(_this).hasClass("arrow_up")){
            // �ж��Ƿ��Ѽ��ع�
            if($("#his_lastgame_detail_"+id).attr("data-id") == 1){
            }else{
                GetHisRecordDetail(id, gameseq, gamesvrentity, relaysvrentity, linetype, teamnumm);
                //IDE_GetHisRecordDetail(id, gameseq, gamesvrentity, relaysvrentity, linetype, teamnumm);
            }

            $(_this).removeClass("arrow_up");
            $(_this).addClass("arrow_down");
            $("#his_lastgame_detail_"+id).show();
        }else{
            $(_this).addClass("arrow_up");
            $(_this).removeClass("arrow_down");
            $("#his_lastgame_detail_"+id).hide();
        }   
    }
    lastgame_arrow.on("click",function(){
        var id=$(this).attr("data-id");
        showRecord(this,id);    
    });

    // �ҵ��ʲ�
    function GetHeroSkin()
    {
        var url = curpro+"//mapps.game.qq.com/yxzj/web201605/GetHeroSkin.php?appid="+appid+"&area="+area+"&partition="+partition + "&roleid=" + roleid +"&r="+Math.random();
        include(url, function(loaded){
            if(!loaded || typeof(GetHeroSkinResult) == "undefined")
            {
                alert("ϵͳ��æ�����Ժ�����");
                return;
            }
//            console.log(GetHeroSkinResult);
            var result = GetHeroSkinResult;
            if(result.iRet != 0)
            {
                alert(result.sMsg);
                return;
            }

            if(typeof(result.data.idip_info) != "undefined")
            {
                $(".level-ico").text(result.data.idip_info.pvplevel);
                // ΢�ź���QͼƬ���޷�����
                // $(".avatar img").attr("src", decodeURIComponent(result.data.idip_info.head_url));
                // $("#nickname").text(decodeURIComponent(result.data.idip_info.charac_name));
                
                grade_level = (result.data.idip_info.grade_level) ? result.data.idip_info.grade_level : 1;
                // alert(rankInfo[grade_level]);
                $(".grade_level").text(rankInfo[grade_level]);
                var img_level = parseInt(grade_level);
				if(img_level < 1) $img_level = 1;
                var grade_level_url = getRankImgByGradeLevel(img_level);
                $(".sco-img").attr("src", grade_level_url);
                /* IDIP����
                if(result.data.idip_info.play_time >= 0)
                {
                    var time = Math.floor(result.data.idip_info.play_time/3600);
                    $(".play_time").text(time);
                }
                */
                var team = "��ս����Ϣ";
                if(result.data.idip_info.team != 0 && result.data.idip_info.team != '')
                {
                    team = decodeURIComponent(result.data.idip_info.team);
                }
                $(".info-id span").text("(" + team + ")");
            }

            if(typeof(result.data.history) != "undefined" && typeof(result.data.hero_skin_list) != "undefined")
            {
                // �ܱ���ʤ����ʤ�ʣ� ��λ��ʤ��ʤ��
                $(".win_count").text(result.data.history.total_win_num);
                $(".hero_count").text(result.data.hero_skin_list.HeroListCount);
                $(".skin_count").text(result.data.hero_skin_list.HeroSkinCount);
            }

            if(typeof(result.data.hero_skin_list) != "undefined")
            {
                $("#hero_count").text(result.data.hero_skin_list["HeroListCount"]);
//                $("#skin_count").text(result.data.hero_skin_list["HeroSkinCount"]);

                var hero_list_str = result.data.hero_skin_list["HeroListStr"];
                var skin_list_str = result.data.hero_skin_list["HeroSkinStr"];

                var hero_list_html = '';
                var hero_skin_html = '';
                
                // add by jim
                loadHeroList(function(res){ // ����ص����߳ɹ�����ִ��
                    var ALLHEROANDSKINS = res;
                    $.each(ALLHEROANDSKINS , function(k,v){
                        var gray_class = "";
                        if(!milo.hasValue(hero_list_str, v.ename)){ // ����ʽ
                            gray_class = "toGray";
                        }
                        var head_url = getHeroHeadById(v.ename);
                        hero_list_html += '<li class=""+ gray_class +" hero_location_"+ v.hero_type +""><img src=""+head_url+"" alt=""><span class="s_hero_name">"+ v.cname +"</span></li>';

                        hero_skin_html += '<li class="hero_skin_list "+ gray_class +" hero_location_"+ v.hero_type +"" id="hero_skin_"+ v.ename +"" style="cursor:pointer;"><img src=""+head_url+"" alt=""><span  class="s_hero_name">"+ v.cname +"</span></li>';
                    });
                    
                    $(".hero_list").html(hero_list_html);
                    $(".hero_skin_list").html(hero_skin_html);

                    // ��ʼ��Ƥ��
                    sel_skin(105);

                    // Ƥ��ѡ��
                    $(".hero_skin_list").on("click", function(){
                        var id = $(this).attr("id");
                        // console.log(id);
                        if(id != undefined){
                        }else{
                            return false;
                        }
                        id = id.split("_");
                        var hero_id = id["2"];
                        // console.log(skin_list_str[hero_id]);

                        sel_skin(hero_id);
                    });

                    // Ƥ��ѡ��
                    function sel_skin(hero_id){
                        $.each(ALLHEROANDSKINS , function(key,val){
                            if(val.ename == hero_id){ 
                                // Ӣ������
                                $(".hero_name").text(val.cname);

                                // Ӣ��ͷ��
                                var head_url = getHeroHeadById(val.ename);
                                $(".hero_pic").attr("src", head_url);
                                var all_skins = val.skin_name.split("|");
                                var skin_list_html = "";
                                var skin_count = 0;  // Ӣ��Ƥ������
                                var skin_has_count = 0;  // ӵ�е�Ƥ������
                                var skin_id = -1;
                                $.each(all_skins, function(k, v){ // ��������Ƥ��
//                                    if(v == "�����ڴ�"){
//                                        return true;
//                                    }
                                    skin_id ++;
                                    
                                    skin_count++;      // 154-myskin-0.jpg

                                    var has_skin_class = "";
                                    var flag = 0;
                                    if(skin_list_str[hero_id] != undefined){
                                        var temp = skin_list_str[hero_id].split('").reverse().join("');
                                        for(var i=0;i<temp.length;i++){
                                            if (temp == null) continue;
                                            var tmp = temp.charAt(i);
                                            if(tmp == 1 && k == i){
                                                if(i == 0 && $("#hero_skin_"+hero_id).hasClass("toGray")){ // û��Ӣ�ۣ�����Ƥ��Ҫ����
                                                    break;
                                                }
                                                flag = 1;
                                                skin_has_count++;
                                                break;
                                            }
                                        }
                                    }

                                    if(flag == 0){ // û�и�Ӣ�ۣ������Ƥ��ҲӦ��
//                                        has_skin_class = "nohasskin";
                                    }
//                                    var skin_id = parseInt(k);
                                    var skin_name = v;
                                    var skin_url = getHeroSkinById(hero_id,skin_id);
                                    skin_list_html += '<li><img class=""+ has_skin_class +"" width="170" height="240" src=""+skin_url+"" alt=""><div class="per_hero_listImghover"><span>δӵ��</span></div><p>"+ skin_name +"</p></li>';
                                });
                                $(".per_noskin").text(skin_count);
//                                $(".per_haskin").text(skin_has_count);
                                $("#skin_list").html(skin_list_html);
                                
                            }
                        });
                    }
                    
                });

            }
        });
    }

    function IDE_GetHeroSkin() {
        IDE_GetHeadInfo(1, function(result) {
            $("#hero_count").text(result.data.hero_count);
            // var hero_list_str = result.data.hero_skin_list["HeroListStr"];
            // var skin_list_str = result.data.hero_skin_list["HeroSkinStr"];
            var heros = result.data.heros;
            var skins = result.data.skins;
            var hero_list_html = '';
            var hero_skin_html = '';
            // add by jim
            loadHeroList(function(res){ // ����ص����߳ɹ�����ִ��
                var ALLHEROANDSKINS = res;
                var initSkinFlag = true
                $.each(ALLHEROANDSKINS , function(k,v){
                    var gray_class = "";
                    if(heros[v.ename] == null){
                        gray_class = "toGray"; // û�и�Ӣ��
                    }else{
                        // if(initSkinFlag){
                        //     initSkinFlag = false
                        //     // ��ʼ��Ƥ��
                        //     sel_skin(v.ename);
                        // }
                    }
                    var head_url = getHeroHeadById(v.ename);
                    hero_list_html += '<li class="' + gray_class + ' hero_location_' + v.hero_type + '"><img src="' + head_url + '" alt=""><span class="s_hero_name">' + v.cname + '</span></li>';
                    hero_skin_html += '<li class="hero_skin_list ' + gray_class + ' hero_location_' + v.hero_type + '" id="hero_skin_' + v.ename + '" style="cursor:pointer;"><img src="' + head_url + '" alt=""><span  class="s_hero_name">' + v.cname + '</span></li>';
                });                
                $(".hero_list").html(hero_list_html);
                $(".hero_skin_list").html(hero_skin_html);

                sel_skin(105);
                // Ƥ��ѡ��
                $(".hero_skin_list").on("click", function(){
                    var id = $(this).attr("id");
                    // console.log(id);
                    if(id != null){
                    } else return false;
                    id = id.split("_");
                    var hero_id = id["2"];
                    sel_skin(hero_id);
                });

                // Ƥ��ѡ��
                function sel_skin(hero_id){
                    $.each(ALLHEROANDSKINS , function(key,val){
                        if(val.ename == hero_id){ 
                            // Ӣ������
                            $(".hero_name").text(val.cname);
                            // Ӣ��ͷ��
                            var head_url = getHeroHeadById(val.ename);
                            $(".hero_pic").attr("src", head_url);
                            var all_skins = val.skin_name.split("|");
                            var skin_list_html = "";
                            var skin_count = 0;  // Ӣ��Ƥ������
                            var skin_has_count = 0;  // ӵ�е�Ƥ������
                            var skin_id = -1;
                            $.each(all_skins, function(k, v){ // ��������Ƥ��
                                skin_id ++;
                                skin_count++;      // 154-myskin-0.jpg
                                var has_skin_class = "";
                                var flag = 0;
                                if(skins[hero_id] != undefined){
                                    var temp = skins[hero_id].split('').reverse().join('');
                                    for(var i=0;i<temp.length;i++){
                                        var tmp = temp.charAt(i);
                                        if (tmp == null) continue;
                                        if(tmp == 1 && k == i){
                                            if(i == 0 && $("#hero_skin_"+hero_id).hasClass("toGray")){ // û��Ӣ�ۣ�����Ƥ��Ҫ����
                                                break;
                                            }
                                            flag = 1;
                                            skin_has_count++;
                                            break;
                                        }
                                    }
                                }

                                if (flag == 0) {
                                    // û�и�Ӣ�ۣ������Ƥ��ҲӦ��
                                }
                                var skin_name = v;
                                var skin_url = getHeroSkinById(hero_id,skin_id);
                                skin_list_html += '<li><img class="' + has_skin_class + '" width="170" height="240" src="' + skin_url + '" alt=""><div class="per_hero_listImghover"><span>δӵ��</span></div><p>' + skin_name + '</p></li>';
                            });
                            $(".per_noskin").text(skin_count);
                            $("#skin_list").html(skin_list_html);
                        }
                    });
                } 
            });
        });
    }

    // ɸѡӢ��
    $(".hero_location").on("click", function(){
        // ����
        $(".hero_list li").show();
        $(".hero_skin_list li").show();

        var id = $(this).attr("data-id");

        $.each($(".hero_location"), function(k, v){
            if($(this).attr("data-id") == id){
                $(this).attr("checked", "checked");
            }
        });

        if(id == 0){  // ȫ��
            $(".hero_list li").show();
            $(".hero_skin_list li").show();
        }else if(id == -1){
            $(".hero_list>li:not(.toGray)").hide();
            $(".hero_skin_list>li:not(.toGray)").hide();
        }else{
            $(".hero_list li").hide();
            $(".hero_skin_list li").hide();
            $(".hero_location_"+id).show();
        }
        
    });

    // �����û�������
    $(".skinSearchBtn").on("click", function(){
        var hero_name = $(this).parent().find(".skinSearchName").val();

        if(hero_name != "" && hero_name != undefined){
            $(".hero_list li").show();
            $(".hero_skin_list li").show();
        }else{
            alert("��ѡ����Ҫ������Ӣ����");
            return false;
        }

        $(".hero_list li").hide();
        $(".hero_skin_list li").hide();

        $(".s_hero_name").each(function(k, v){
            if($(this).text().indexOf(hero_name) >= 0){
                $(this).parent().show();
            }
        });
    });

    // ����ģ��
    // 2018-07-09: �ж�������°�milo (milo_bundle/milo.js), ������ biz.dialog �ļ�  by sonic
    function TGDialogS(e){
        var url = window.location.href;
        if(typeof defineconflict == "function"){   
            need("biz.dialog",function(Dialog){
               Dialog.show({
                   id:e,
                   bgcolor:"#000", 
                   opacity:50
               });
           });
        }else{
            need("biz.dialog-min",function(Dialog){
                Dialog.show({
                  id:e,
                  bgcolor:"#000", // ���������֡�����ɫ����ʽΪ"#FF6600"�����޸ģ�Ĭ��Ϊ"#fff"
                  opacity:50      // ���������֡���͸���ȣ���ʽΪ��10-100������ѡ
                });
            });
        }
    };
    function closeDialog(){  
        if(typeof defineconflict == "function"){
            need("biz.dialog",function(Dialog){
                  Dialog.hide();
              });
        }else{
            need("biz.dialog-min",function(Dialog){
                  Dialog.hide();
            });
        }
    };

    function setLoginAuthTxt(txt) {
        txt && $("#se-checkbox-txt").text(txt)
    }

    // ����sCustomTipsMiloPIPֵ �Զ�������Ȩ�İ�
    setTimeout(function(){
        setLoginAuthTxt(window.sCustomTipsMiloPIP)
    }, 2000)

    function setPrivateLink() {
        setTimeout(function(){
            window.GameFooter && window.GameFooter.addLinks({
                service: {link: "https://game.qq.com/tencent_other_contract.shtml"},
                private: {text: "������ҫ��˽����ָ��",link: "https://rule.tencent.com/rule/preview/d277ee20-2709-4cd5-882b-cbd485753346"},
                children: {link: "https://game.qq.com/tencent_other_children_privacy.shtml"}
            });
        }, 500);
    }
    setPrivateLink();
}
catch(e)
{
    console.error("logic.js ִ���쳣", e);
}