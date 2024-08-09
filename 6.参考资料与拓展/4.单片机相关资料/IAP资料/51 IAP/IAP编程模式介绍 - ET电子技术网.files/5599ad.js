document.writeln("<div style=\"position:absolute;border:1px solid #000;right:0;\" id=\"ad\"><a href=\"http:\/\/www.5599.net\/?etdz\" target=\"_blank\"><img src=\"http:\/\/www.et-dz.com\/templets\/images\/240X180.gif\" width=\"240\" height=\"180\" alt=\"5599ÍøÖ·µ¼º½\" \/><\/a><\/div>");
document.writeln("<script language=\"JavaScript\" type=\"text\/javascript\">");
document.writeln("function rightBottomAd(){");
document.writeln(" var abc = document.getElementById(\"ad\");");
document.writeln(" abc.style.top = document.documentElement.scrollTop+document.documentElement.clientHeight-180+\"px\"; ");
document.writeln(" setTimeout(function(){rightBottomAd();},50);");
document.writeln("}");
document.writeln("rightBottomAd();");
document.writeln("<\/script>")