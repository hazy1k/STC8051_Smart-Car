var addcode_f=false;function addcode(){if(!addcode_f){if (chkdiv('ob_code')) {document.getElementById('ob_code').innerHTML='验证码：<input name="CodeStr" type="text" size="6" maxlength="20" /> <img id="ob_codeimg" src="/inc/code.asp?s=426245" style="cursor:hand;border:1px solid #ccc;vertical-align:top;" onclick="this.src=\'/inc/code.asp?s=426245&t=\'+ Math.random();" alt="如果看不清数字或字母?请点一下换一个!" title="如果看不清数字或字母?请点一下换一个!" /><input type="hidden" name="ob_codename" value="426245" />  ';}}addcode_f=true;}
var ShowDigg ;
function diggit(logid){
	
	var Ajax = new oAjax("/ajaxServer.asp?action=digglog&fromurl=",show_returnsave);
	var arrKey = new Array("logid","");
	var arrValue = new Array(logid,"");
	Ajax.Post(arrKey,arrValue);
	
}
function show_returnsave(arrobj){
	if (arrobj){
		if (arrobj.length == 4) {
			ShowDigg ='\n<div class="digg_list" style="float: right; display:inline; margin: 0 10px 5px 0; width: 45px; height: 55px; background: url(/Images/digg.gif) no-repeat left top; text-align: center; ">\n	<div class="digg_number" style="width:45px;padding: 10px 0 11px 0;font-size:18px;font-weight:600;color:#333;font-family:tahoma,Arial,Helvetica,sans-serif;line-height:1.0;">$diggnum$</div>\n	<div class="digg_submit" style=" padding: 3px 0 0 6px;line-height:1.0;letter-spacing: 6px; "><a href="javascript:void(null)" onclick="diggit($logid$);" style="font-size:12px;line-height:1.0;">$showmsg$</a></div>\n</div>\n';
			ShowDigg = ShowDigg.replace('$diggnum$',arrobj[3])
			ShowDigg = ShowDigg.replace('$logid$',arrobj[2])
			ShowDigg = ShowDigg.replace('$showmsg$',arrobj[0])
			document.getElementById("ob_logd"+arrobj[2]).innerHTML = ShowDigg;
			return false;
		}
		switch (arrobj[1]){
		case '1':
			var oDialog = new dialog("/");
			oDialog.init();
			oDialog.set('src',arrobj[1]);
			oDialog.event(arrobj[0],'');
			oDialog.button('dialogOk',"");
			break;
		case '2':
			var oDialog = new dialog("/");
			oDialog.init();
			oDialog.set('src',arrobj[1]);
			oDialog.event(arrobj[0],'');
			oDialog.button('dialogOk',"");
			break;
		}
		}
	}
