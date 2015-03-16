function initBubble(b) {
    $(b).append('<span class="sombraH"></span><span class="sombraV"></span><span class="sombraV2"></span><span class="punta"></span>');
    var j = $("#ContenedorMapa").width();
    var f = $("#ContenedorMapa").height();
    var d = b.offsetLeft;
    var c = b.offsetTop;
    var g = 30;
    var i = $(b).children("span.info").height();
    var h = 140;
    var k = i + $(b).height();
    if ((d + h + g) <= j) {
        if ((k + g) > c) {
            var a = 17;
            var e = 17;
            $(b).children("span.punta").css({
                background: "url(http://www.bcn.cat/planol_bcn/img/bubble/punta1.png) 0 0 no-repeat",
                margin: a + "px 0 0 " + e + "px"
            });
            $(b).children("span.info").css({
                margin: (a + 22) + "px 0 0 " + (e + 8) + "px"
            });
            $(b).children("div#FondoDireccionActual").css({
                margin: (a + 22) + "px 0 0 " + (e + 8) + "px"
            });
            $(b).children("span.sombraH").css({
                "margin-top": (a + i + 44) + "px",
                "margin-left": e + "px"
            });
            $(b).children("span.sombraV").css({
                "margin-top": (a + 34) + "px",
                "margin-left": e + "px",
                height: (i + 10)
                });
            $(b).children("span.sombraV2").css({
                "margin-top": (a + 24) + "px",
                "margin-left": e + "px"
            });
        } else {
            var a = -18;
            var e = 18;
            $(b).children("span.punta").css({
                background: "url(http://www.bcn.cat/planol_bcn/img/bubble/punta3.png) 0 0 no-repeat",
                margin: a + "px 0 0 " + e + "px"
            });
            $(b).children("span.info").css({
                margin: (a - i - 21) + "px 0 0 " + (e + 8) + "px"
            });
            $(b).children("div#FondoDireccionActual").css({
                margin: (a - i - 21) + "px 0 0 " + (e + 8) + "px"
            });
            $(b).children("span.sombraH").css({
                "margin-top": (a + 1) + "px",
                "margin-left": e + "px"
            });
            $(b).children("span.sombraV").css({
                margin: (a - i - 9) + "px 0 0 " + e + "px",
                height: (i + 10)
                });
            $(b).children("span.sombraV2").css({
                "margin-top": (a - i - 19) + "px",
                "margin-left": e + "px"
            });
        }
    } else {
        if ((k + g) > c) {
            var a = 18;
            var e = -157;
            $(b).children("span.punta").css({
                background: "url(http://www.bcn.cat/planol_bcn/img/bubble/punta2.png) 0 0 no-repeat",
                margin: a + "px 0 0 " + (e + 122) + "px"
            });
            $(b).children("span.info").css({
                margin: (a + 22) + "px 0 0 " + (e + 8) + "px"
            });
            $(b).children("div#FondoDireccionActual").css({
                margin: (a + 22) + "px 0 0 " + (e + 8) + "px"
            });
            $(b).children("span.sombraH").css({
                margin: (a + i + 44) + "px 0 0 " + e + "px"
            });
            $(b).children("span.sombraV").css({
                "margin-top": (a + 34) + "px",
                "margin-left": e + "px",
                height: (i + 10)
                });
            $(b).children("span.sombraV2").css({
                "margin-top": (a + 24) + "px",
                "margin-left": e + "px"
            });
        } else {
            var a = -17;
            var e = -155;
            $(b).children("span.punta").css({
                background: "url(http://www.bcn.cat/planol_bcn/img/bubble/punta4.png) 0 0 no-repeat",
                margin: a + "px 0 0 " + (e + 113) + "px"
            });
            $(b).children("span.info").css({
                margin: (a - i - 21) + "px 0 0 " + (e + 8) + "px"
            });
            $(b).children("div#FondoDireccionActual").css({
                margin: (a - i - 21) + "px 0 0 " + (e + 8) + "px"
            });
            $(b).children("span.sombraH").css({
                margin: (a + 1) + "px 0 0 " + e + "px"
            });
            $(b).children("span.sombraV").css({
                margin: (a - i - 9) + "px 0 0 " + e + "px",
                height: (i + 10)
                });
            $(b).children("span.sombraV2").css({
                "margin-top": (a - i - 19) + "px",
                "margin-left": e + "px"
            });
        }
    }
    //ELAZOS $(b).pngFix();
}
function iconOver(a) {
    if (!$(a).hasClass("iniciat")) {
        initBubble(a);
        $(a).addClass("iniciat");
    }
    $(a).children("span").css("display", "block");
}
function iconOut(a) {
    $(a).children("span").css("display", "none");
} /*(function(aD) {
    var aA,
    at,
    au,
    aG,
    ai,
    ay,
    aj,
    aB,
    an,
    ag,
    ap = 0,
    aF = {},
    aC = [],
    ao = 0,
    aE = {},
    az = [],
    al = null,
    av = new Image,
    aa = /\.(jpg|gif|png|bmp|jpeg)(.*)?$/i,
    P = /[^\.]\.(swf)\s*$/i,
    ab,
    ac = 1,
    am = 0,
    ar = "",
    aq,
    ax,
    aw = false,
    ah = aD.extend(aD("<div/>")[0], {
        prop: 0
    }),
    ad = aD.browser.msie && aD.browser.version < 7 && !window.XMLHttpRequest,
    ae = function() {
        at.hide();
        av.onerror = av.onload = null;
        al && al.abort();
        aA.empty();
    },
    af = function() {
        if (false === aF.onError(aC, ap, aF)) {
            at.hide();
            aw = false;
        } else {
            aF.titleShow = false;
            aF.width = "auto";
            aF.height = "auto";
            aA.html('<p id="fancybox-error">The requested content cannot be loaded.<br />Please try again later.</p>');
            ak();
        }
    },
    R = function() {
        var d = aC[ap],
        f,
        j,
        i,
        h,
        e,
        b;
        ae();
        aF = aD.extend({}, aD.fn.fancybox.defaults, typeof aD(d).data("fancybox") == "undefined" ? aF: aD(d).data("fancybox"));
        b = aF.onStart(aC, ap, aF);
        if (b === false) {
            aw = false;
        } else {
            if (typeof b == "object") {
                aF = aD.extend(aF, b);
            }
            i = aF.title || (d.nodeName ? aD(d).attr("title") : d.title) || "";
            if (d.nodeName && !aF.orig) {
                aF.orig = aD(d).children("img:first").length ? aD(d).children("img:first") : aD(d);
            }
            if (i === "" && aF.orig && aF.titleFromAlt) {
                i = aF.orig.attr("alt");
            }
            f = aF.href || (d.nodeName ? aD(d).attr("href") : d.href) || null;
            if (/^(?:javascript)/i.test(f) || f == "#") {
                f = null;
            }
            if (aF.type) {
                j = aF.type;
                if (!f) {
                    f = aF.content;
                }
            } else {
                if (aF.content) {
                    j = "html";
                } else {
                    if (f) {
                        j = f.match(aa) ? "image": f.match(P) ? "swf": aD(d).hasClass("iframe") ? "iframe": f.indexOf("#") === 0 ? "inline": "ajax";
                    }
                }
            }
            if (j) {
                if (j == "inline") {
                    d = f.substr(f.indexOf("#"));
                    j = aD(d).length > 0 ? "inline": "ajax";
                }
                aF.type = j;
                aF.href = f;
                aF.title = i;
                if (aF.autoDimensions) {
                    if (aF.type == "html" || aF.type == "inline" || aF.type == "ajax") {
                        aF.width = "auto";
                        aF.height = "auto";
                    } else {
                        aF.autoDimensions = false;
                    }
                }
                if (aF.modal) {
                    aF.overlayShow = true;
                    aF.hideOnOverlayClick = false;
                    aF.hideOnContentClick = false;
                    aF.enableEscapeButton = false;
                    aF.showCloseButton = false;
                }
                aF.padding = parseInt(aF.padding, 10);
                aF.margin = parseInt(aF.margin, 10);
                aA.css("padding", aF.padding + aF.margin);
                aD(".fancybox-inline-tmp").unbind("fancybox-cancel").bind("fancybox-change", function() {
                    aD(this).replaceWith(ay.children());
                }); 
                switch (j) {
                case "html":
                    aA.html(aF.content);
                    ak();
                    break;
                case "inline":
                    if (aD(d).parent().is("#fancybox-content") === true) {
                        aw = false;
                        break;
                    }
                    aD('<div class="fancybox-inline-tmp" />').hide().insertBefore(aD(d)).bind("fancybox-cleanup", function() {
                        aD(this).replaceWith(ay.children());
                    }).bind("fancybox-cancel", function() {
                        aD(this).replaceWith(aA.children());
                    });
                    aD(d).appendTo(aA);
                    ak();
                    break;
                case "image":
                    aw = false;
                    aD.fancybox.showActivity();
                    av = new Image;
                    av.onerror = function() {
                        af();
                    };
                    av.onload = function() {
                        aw = true;
                        av.onerror = av.onload = null;
                        aF.width = av.width;
                        aF.height = av.height;
                        aD("<img />").attr({
                            id: "fancybox-img",
                            src: av.src,
                            alt: aF.title
                        }).appendTo(aA);
                        k();
                    };
                    av.src = f;
                    break;
                case "swf":
                    aF.scrolling = "no";
                    h = '<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" width="' + aF.width + '" height="' + aF.height + '"><param name="movie" value="' + f + '"></param>';
                    e = "";
                    aD.each(aF.swf, function(l, m) {
                        h += '<param name="' + l + '" value="' + m + '"></param>';
                        e += " " + l + '="' + m + '"';
                    });
                    h += '<embed src="' + f + '" type="application/x-shockwave-flash" width="' + aF.width + '" height="' + aF.height + '"' + e + "></embed></object>";
                    aA.html(h);
                    ak();
                    break;
                case "ajax":
                    aw = false;
                    aD.fancybox.showActivity();
                    aF.ajax.win = aF.ajax.success;
                    al = aD.ajax(aD.extend({}, aF.ajax, {
                        url: f,
                        data: aF.ajax.data || {},
                        error: function(l) {
                            l.status > 0 && af();
                        },
                        success: function(l, n, m) {
                            if ((typeof m == "object" ? m: al).status == 200) {
                                if (typeof aF.ajax.win == "function") {
                                    b = aF.ajax.win(f, l, n, m);
                                    if (b === false) {
                                        at.hide();
                                        return;
                                    } else {
                                        if (typeof b == "string" || typeof b == "object") {
                                            l = b;
                                        }
                                    }
                                }
                                aA.html(l);
                                ak();
                            }
                        }
                    }));
                    break;
                case "iframe":
                    k();
                }
            } else {
                af();
            }
        }
    },
    ak = function() {
        var b = aF.width,
        d = aF.height;
        b = b.toString().indexOf("%") > -1 ? parseInt((aD(window).width() - aF.margin * 2) * parseFloat(b) / 100, 10) + "px": b == "auto" ? "auto": b + "px";
        d = d.toString().indexOf("%") > -1 ? parseInt((aD(window).height() - aF.margin * 2) * parseFloat(d) / 100, 10) + "px": d == "auto" ? "auto": d + "px";
        aA.wrapInner('<div style="width:' + b + ";height:" + d + ";overflow: " + (aF.scrolling == "auto" ? "auto": aF.scrolling == "yes" ? "scroll": "hidden") + ';position:relative;"></div>');
        aF.width = aA.width();
        aF.height = aA.height();
        k();
    },
    k = function() {
        var b,
        d;
        at.hide();
        if (aG.is(":visible") && false === aE.onCleanup(az, ao, aE)) {
            aD.event.trigger("fancybox-cancel");
            aw = false;
        } else {
            aw = true;
            aD(ay.add(au)).unbind();
            aD(window).unbind("resize.fb scroll.fb");
            aD(document).unbind("keydown.fb");
            aG.is(":visible") && aE.titlePosition !== "outside" && aG.css("height", aG.height());
            az = aC;
            ao = ap;
            aE = aF;
            if (aE.overlayShow) {
                au.css({
                    "background-color": aE.overlayColor,
                    opacity: aE.overlayOpacity,
                    cursor: aE.hideOnOverlayClick ? "pointer": "auto",
                    height: aD(document).height()
                    });
                if (!au.is(":visible")) {
                    ad && aD("select:not(#fancybox-tmp select)").filter(function() {
                        return this.style.visibility !== "hidden";
                    }).css({
                        visibility: "hidden"
                    }).one("fancybox-cleanup", function() {
                        this.style.visibility = "inherit";
                    });
                    au.show();
                }
            } else {
                au.hide();
            }
            ax = a();
            ar = aE.title || "";
            am = 0;
            aB.empty().removeAttr("style").removeClass();
            if (aE.titleShow !== false) {
                if (aD.isFunction(aE.titleFormat)) {
                    b = aE.titleFormat(ar, az, ao, aE);
                } else {
                    b = ar && ar.length ? aE.titlePosition == "float" ? '<table id="fancybox-title-float-wrap" cellpadding="0" cellspacing="0"><tr><td id="fancybox-title-float-left"></td><td id="fancybox-title-float-main">' + ar + '</td><td id="fancybox-title-float-right"></td></tr></table>': '<div id="fancybox-title-' + aE.titlePosition + '">' + ar + "</div>": false;
                }
                ar = b;
                if (! (!ar || ar === "")) {
                    aB.addClass("fancybox-title-" + aE.titlePosition).html(ar).appendTo("body").show();
                    switch (aE.titlePosition) {
                    case "inside":
                        aB.css({
                            width:
                            ax.width - aE.padding * 2,
                            marginLeft: aE.padding,
                            marginRight: aE.padding
                        });
                        am = aB.outerHeight(true);
                        aB.appendTo(ai);
                        ax.height += am;
                        break;
                    case "over":
                        aB.css({
                            marginLeft:
                            aE.padding,
                            width: ax.width - aE.padding * 2,
                            bottom: aE.padding
                        }).appendTo(ai);
                        break;
                    case "float":
                        aB.css("left", parseInt((aB.width() - ax.width - 40) / 2, 10) * -1).appendTo(aG);
                        break;
                    default:
                        aB.css({
                            width:
                            ax.width - aE.padding * 2,
                            paddingLeft: aE.padding,
                            paddingRight: aE.padding
                        }).appendTo(aG);
                    }
                }
            }
            aB.hide();
            if (aG.is(":visible")) {
                aD(aj.add(an).add(ag)).hide();
                b = aG.position();
                aq = {
                    top: b.top,
                    left: b.left,
                    width: aG.width(),
                    height: aG.height()
                    };
                d = aq.width == ax.width && aq.height == ax.height;
                ay.fadeTo(aE.changeFade, 0.3, function() {
                    var e = function() {
                        ay.html(aA.contents()).fadeTo(aE.changeFade, 1, w);
                    };
                    aD.event.trigger("fancybox-change");
                    ay.empty().removeAttr("filter").css({
                        "border-width": aE.padding,
                        width: ax.width - aE.padding * 2,
                        height: aF.autoDimensions ? "auto": ax.height - am - aE.padding * 2
                    });
                    if (d) {
                        e();
                    } else {
                        ah.prop = 0;
                        aD(ah).animate({
                            prop: 1
                        }, {
                            duration: aE.changeSpeed,
                            easing: aE.easingChange,
                            step: x,
                            complete: e
                        });
                    }
                });
            } else {
                aG.removeAttr("style");
                ay.css("border-width", aE.padding);
                if (aE.transitionIn == "elastic") {
                    aq = H();
                    ay.html(aA.contents());
                    aG.show();
                    if (aE.opacity) {
                        ax.opacity = 0;
                    }
                    ah.prop = 0;
                    aD(ah).animate({
                        prop: 1
                    }, {
                        duration: aE.speedIn,
                        easing: aE.easingIn,
                        step: x,
                        complete: w
                    });
                } else {
                    aE.titlePosition == "inside" && am > 0 && aB.show();
                    ay.css({
                        width: ax.width - aE.padding * 2,
                        height: aF.autoDimensions ? "auto": ax.height - am - aE.padding * 2
                    }).html(aA.contents());
                    aG.css(ax).fadeIn(aE.transitionIn == "none" ? 0: aE.speedIn, w);
                }
            }
        }
    },
    c = function() {
        if (aE.enableEscapeButton || aE.enableKeyboardNav) {
            aD(document).bind("keydown.fb", function(b) {
                if (b.keyCode == 27 && aE.enableEscapeButton) {
                    b.preventDefault();
                    aD.fancybox.close();
                } else {
                    if ((b.keyCode == 37 || b.keyCode == 39) && aE.enableKeyboardNav && b.target.tagName !== "INPUT" && b.target.tagName !== "TEXTAREA" && b.target.tagName !== "SELECT") {
                        b.preventDefault();
                        aD.fancybox[b.keyCode == 37 ? "prev": "next"]();
                    }
                }
            });
        }
        if (aE.showNavArrows) {
            if (aE.cyclic && az.length > 1 || ao !== 0) {
                an.show();
            }
            if (aE.cyclic && az.length > 1 || ao != az.length - 1) {
                ag.show();
            }
        } else {
            an.hide();
            ag.hide();
        }
    },
    w = function() {
        if (!aD.support.opacity) {
            ay.get(0).style.removeAttribute("filter");
            aG.get(0).style.removeAttribute("filter");
        }
        aF.autoDimensions && ay.css("height", "auto");
        aG.css("height", "auto");
        ar && ar.length && aB.show();
        aE.showCloseButton && aj.show();
        c();
        aE.hideOnContentClick && ay.bind("click", aD.fancybox.close);
        aE.hideOnOverlayClick && au.bind("click", aD.fancybox.close);
        aD(window).bind("resize.fb", aD.fancybox.resize);
        aE.centerOnScroll && aD(window).bind("scroll.fb", aD.fancybox.center);
        if (aE.type == "iframe") {
            aD('<iframe id="fancybox-frame" name="fancybox-frame' + (new Date).getTime() + '" frameborder="0" hspace="0" ' + (aD.browser.msie ? 'allowtransparency="true""': "") + ' scrolling="' + aF.scrolling + '" src="' + aE.href + '"></iframe>').appendTo(ay);
        }
        aG.show();
        aw = false;
        aD.fancybox.center();
        aE.onComplete(az, ao, aE);
        var b,
        d;
        if (az.length - 1 > ao) {
            b = az[ao + 1].href;
            if (typeof b !== "undefined" && b.match(aa)) {
                d = new Image;
                d.src = b;
            }
        }
        if (ao > 0) {
            b = az[ao - 1].href;
            if (typeof b !== "undefined" && b.match(aa)) {
                d = new Image;
                d.src = b;
            }
        }
    },
    x = function(b) {
        var d = {
            width: parseInt(aq.width + (ax.width - aq.width) * b, 10),
            height: parseInt(aq.height + (ax.height - aq.height) * b, 10),
            top: parseInt(aq.top + (ax.top - aq.top) * b, 10),
            left: parseInt(aq.left + (ax.left - aq.left) * b, 10)
            };
        if (typeof ax.opacity !== "undefined") {
            d.opacity = b < 0.5 ? 0.5: b;
        }
        aG.css(d);
        ay.css({
            width: d.width - aE.padding * 2,
            height: d.height - am * b - aE.padding * 2
        });
    },
    C = function() {
        return [aD(window).width() - aE.margin * 2, aD(window).height() - aE.margin * 2, aD(document).scrollLeft() + aE.margin, aD(document).scrollTop() + aE.margin];
    },
    a = function() {
        var b = C(),
        d = {},
        f = aE.autoScale,
        e = aE.padding * 2;
        d.width = aE.width.toString().indexOf("%") > -1 ? parseInt(b[0] * parseFloat(aE.width) / 100, 10) : aE.width + e;
        d.height = aE.height.toString().indexOf("%") > -1 ? parseInt(b[1] * parseFloat(aE.height) / 100, 10) : aE.height + e;
        if (f && (d.width > b[0] || d.height > b[1])) {
            if (aF.type == "image" || aF.type == "swf") {
                f = aE.width / aE.height;
                if (d.width > b[0]) {
                    d.width = b[0];
                    d.height = parseInt((d.width - e) / f + e, 10);
                }
                if (d.height > b[1]) {
                    d.height = b[1];
                    d.width = parseInt((d.height - e) * f + e, 10);
                }
            } else {
                d.width = Math.min(d.width, b[0]);
                d.height = Math.min(d.height, b[1]);
            }
        }
        d.top = parseInt(Math.max(b[3] - 20, b[3] + (b[1] - d.height - 40) * 0.5), 10);
        d.left = parseInt(Math.max(b[2] - 20, b[2] + (b[0] - d.width - 40) * 0.5), 10);
        return d;
    },
    H = function() {
        var b = aF.orig ? aD(aF.orig) : false,
        d = {};
        if (b && b.length) {
            d = b.offset();
            d.top += parseInt(b.css("paddingTop"), 10) || 0;
            d.left += parseInt(b.css("paddingLeft"), 10) || 0;
            d.top += parseInt(b.css("border-top-width"), 10) || 0;
            d.left += parseInt(b.css("border-left-width"), 10) || 0;
            d.width = b.width();
            d.height = b.height();
            d = {
                width: d.width + aE.padding * 2,
                height: d.height + aE.padding * 2,
                top: d.top - aE.padding - 20,
                left: d.left - aE.padding - 20
            };
        } else {
            b = C();
            d = {
                width: aE.padding * 2,
                height: aE.padding * 2,
                top: parseInt(b[3] + b[1] * 0.5, 10),
                left: parseInt(b[2] + b[0] * 0.5, 10)
                };
        }
        return d;
    },
    g = function() {
        if (at.is(":visible")) {
            aD("div", at).css("top", ac * -40 + "px");
            ac = (ac + 1) % 12;
        } else {
            clearInterval(ab);
        }
    };
    aD.fn.fancybox = function(b) {
        if (!aD(this).length) {
            return this;
        }
        aD(this).data("fancybox", aD.extend({}, b, aD.metadata ? aD(this).metadata() : {})).unbind("click.fb").bind("click.fb", function(d) {
            d.preventDefault();
            if (!aw) {
                aw = true;
                aD(this).blur();
                aC = [];
                ap = 0;
                d = aD(this).attr("rel") || "";
                if (!d || d == "" || d === "nofollow") {
                    aC.push(this);
                } else {
                    aC = aD("a[rel=" + d + "], area[rel=" + d + "]");
                    ap = aC.index(this);
                }
                R();
            }
        });
        return this;
    };
    aD.fancybox = function(b, d) {
        var h;
        if (!aw) {
            aw = true;
            h = typeof d !== "undefined" ? d: {};
            aC = [];
            ap = parseInt(h.index, 10) || 0;
            if (aD.isArray(b)) {
                for (var f = 0, e = b.length; f < e; f++) {
                    if (typeof b[f] == "object") {
                        aD(b[f]).data("fancybox", aD.extend({}, h, b[f]));
                    } else {
                        b[f] = aD({}).data("fancybox", aD.extend({
                            content: b[f]
                            }, h));
                    }
                }
                aC = jQuery.merge(aC, b);
            } else {
                if (typeof b == "object") {
                    aD(b).data("fancybox", aD.extend({}, h, b));
                } else {
                    b = aD({}).data("fancybox", aD.extend({
                        content: b
                    }, h));
                }
                aC.push(b);
            }
            if (ap > aC.length || ap < 0) {
                ap = 0;
            }
            R();
        }
    };
    aD.fancybox.showActivity = function() {
        clearInterval(ab);
        at.show();
        ab = setInterval(g, 66);
    };
    aD.fancybox.hideActivity = function() {
        at.hide();
    };
    aD.fancybox.next = function() {
        return aD.fancybox.pos(ao + 1);
    };
    aD.fancybox.prev = function() {
        return aD.fancybox.pos(ao - 1);
    };
    aD.fancybox.pos = function(b) {
        if (!aw) {
            b = parseInt(b);
            aC = az;
            if (b > -1 && b < az.length) {
                ap = b;
                R();
            } else {
                if (aE.cyclic && az.length > 1) {
                    ap = b >= az.length ? 0: az.length - 1;
                    R();
                }
            }
        }
    };
    aD.fancybox.cancel = function() {
        if (!aw) {
            aw = true;
            aD.event.trigger("fancybox-cancel");
            ae();
            aF.onCancel(aC, ap, aF);
            aw = false;
        }
    };
    aD.fancybox.close = function() {
        function b() {
            au.fadeOut("fast");
            aB.empty().hide();
            aG.hide();
            aD.event.trigger("fancybox-cleanup");
            ay.empty();
            aE.onClosed(az, ao, aE);
            az = aF = [];
            ao = ap = 0;
            aE = aF = {};
            aw = false;
        }
        if (! (aw || aG.is(":hidden"))) {
            aw = true;
            if (aE && false === aE.onCleanup(az, ao, aE)) {
                aw = false;
            } else {
                ae();
                aD(aj.add(an).add(ag)).hide();
                aD(ay.add(au)).unbind();
                aD(window).unbind("resize.fb scroll.fb");
                aD(document).unbind("keydown.fb");
                ay.find("iframe").attr("src", ad && /^https/i.test(window.location.href || "") ? "javascript:void(false)": "about:blank");
                aE.titlePosition !== "inside" && aB.empty();
                aG.stop();
                if (aE.transitionOut == "elastic") {
                    aq = H();
                    var d = aG.position();
                    ax = {
                        top: d.top,
                        left: d.left,
                        width: aG.width(),
                        height: aG.height()
                        };
                    if (aE.opacity) {
                        ax.opacity = 1;
                    }
                    aB.empty().hide();
                    ah.prop = 1;
                    aD(ah).animate({
                        prop: 0
                    }, {
                        duration: aE.speedOut,
                        easing: aE.easingOut,
                        step: x,
                        complete: b
                    });
                } else {
                    aG.fadeOut(aE.transitionOut == "none" ? 0: aE.speedOut, b);
                }
            }
        }
    };
    aD.fancybox.resize = function() {
        au.is(":visible") && au.css("height", aD(document).height());
        aD.fancybox.center(true);
    };
    aD.fancybox.center = function(b) {
        var d,
        e;
        if (!aw) {
            e = b === true ? 1: 0;
            d = C(); ! e && (aG.width() > d[0] || aG.height() > d[1]) || aG.stop().animate({
                top: parseInt(Math.max(d[3] - 20, d[3] + (d[1] - ay.height() - 40) * 0.5 - aE.padding)),
                left: parseInt(Math.max(d[2] - 20, d[2] + (d[0] - ay.width() - 40) * 0.5 - aE.padding))
                }, typeof b == "number" ? b: 200);
        }
    };
    aD.fancybox.init = function() {
        if (!aD("#fancybox-wrap").length) {
            aD("body").append(aA = aD('<div id="fancybox-tmp"></div>'), at = aD('<div id="fancybox-loading"><div></div></div>'), au = aD('<div id="fancybox-overlay"></div>'), aG = aD('<div id="fancybox-wrap"></div>'));
            ai = aD('<div id="fancybox-outer"></div>').append('<div class="fancybox-bg" id="fancybox-bg-n"></div><div class="fancybox-bg" id="fancybox-bg-ne"></div><div class="fancybox-bg" id="fancybox-bg-e"></div><div class="fancybox-bg" id="fancybox-bg-se"></div><div class="fancybox-bg" id="fancybox-bg-s"></div><div class="fancybox-bg" id="fancybox-bg-sw"></div><div class="fancybox-bg" id="fancybox-bg-w"></div><div class="fancybox-bg" id="fancybox-bg-nw"></div>').appendTo(aG);
            ai.append(ay = aD('<div id="fancybox-content"></div>'), aj = aD('<a id="fancybox-close"></a>'), aB = aD('<div id="fancybox-title"></div>'), an = aD('<a href="javascript:;" id="fancybox-left"><span class="fancy-ico" id="fancybox-left-ico"></span></a>'), ag = aD('<a href="javascript:;" id="fancybox-right"><span class="fancy-ico" id="fancybox-right-ico"></span></a>'));
            aj.click(aD.fancybox.close);
            at.click(aD.fancybox.cancel);
            an.click(function(b) {
                b.preventDefault();
                aD.fancybox.prev();
            });
            ag.click(function(b) {
                b.preventDefault();
                aD.fancybox.next();
            });
            aD.fn.mousewheel && aG.bind("mousewheel.fb", function(b, d) {
                if (aw) {
                    b.preventDefault();
                } else {
                    if (aD(b.target).get(0).clientHeight == 0 || aD(b.target).get(0).scrollHeight === aD(b.target).get(0).clientHeight) {
                        b.preventDefault();
                        aD.fancybox[d > 0 ? "prev": "next"]();
                    }
                }
            });
            aD.support.opacity || aG.addClass("fancybox-ie");
            if (ad) {
                at.addClass("fancybox-ie6");
                aG.addClass("fancybox-ie6");
                aD('<iframe id="fancybox-hide-sel-frame" src="' + (/^https/i.test(window.location.href || "") ? "javascript:void(false)": "about:blank") + '" scrolling="no" border="0" frameborder="0" tabindex="-1"></iframe>').prependTo(ai);
            }
        }
    };
    aD.fn.fancybox.defaults = {
        padding: 10,
        margin: 40,
        opacity: false,
        modal: false,
        cyclic: false,
        scrolling: "auto",
        width: 560,
        height: 340,
        autoScale: true,
        autoDimensions: true,
        centerOnScroll: false,
        ajax: {},
        swf: {
            wmode: "transparent"
        },
        hideOnOverlayClick: true,
        hideOnContentClick: false,
        overlayShow: true,
        overlayOpacity: 0.7,
        overlayColor: "#777",
        titleShow: true,
        titlePosition: "float",
        titleFormat: null,
        titleFromAlt: false,
        transitionIn: "fade",
        transitionOut: "fade",
        speedIn: 300,
        speedOut: 300,
        changeSpeed: 300,
        changeFade: "fast",
        easingIn: "swing",
        easingOut: "swing",
        showCloseButton: true,
        showNavArrows: true,
        enableEscapeButton: true,
        enableKeyboardNav: true,
        onStart: function() {},
        onCancel: function() {},
        onComplete: function() {},
        onCleanup: function() {},
        onClosed: function() {},
        onError: function() {}
    };
    aD(document).ready(function() {
        aD.fancybox.init();
    });
})(jQuery);*/ (function(a) {
    a.fn.exists = function() {
        return this.length > 0;
    };
    a.fn.map_guia = function(G) {
        if (this.length > 1) {
            MapObjects = Array();
            this.each(function(o) {
                MapObjects[o] = a(this).map_guia(a.fn.map_guia.options[o]);
            });
            return MapObjects;
        } else {
            if (this.length == 0) {
                return false;
            }
        }
        me = a(this);
        el = this;
        defaults = {
            IdMap: "",
            ShowMapaSituacio: true,
            ShowDesplazamiento: true,
            ShowSlider: true,
            ShowImgEscala: true,
            ShowStatusCoords: true,
            UseHistory: true,
            ZoomDoubleClick: true,
            ZoomMouse: true,
            ShowPopUpLinks: true,
            queryEQ: "http://www.bcn.es/cgi-bin/veure_eq.pl?v=planol&id=",
            queryEQs: "http://w20.bcn.cat/GuiaMap/InfoEquip.aspx",
            DragMap: true,
            MapaSituacioVisible: false,
            queryMapa: "http://w20.bcn.cat/GuiaHandler/GuiaHandler.ashx/Guia.cca?",
            MapaParams: "",
            prevQueryMapaParams: "",
            prevHash: "",
            queryWS: "http://w20.bcn.cat/GuiaMap/JSON_Equips.aspx",
            centroUTMX: 27601010,
            centroUTMY: 83987710,
            centroGuiaX: 11200000,
            centroGuiaY: 11200000,
            minzoom: 0,
            maxzoom: 6,
            escala: [32000, 16000, 8000, 4000, 2000, 1000, 500, 250],
            escala_grafica: ["http://w20.bcn.cat/GuiaMap/img/escala_grafica_1.gif", "http://w20.bcn.cat/GuiaMap/img/escala_grafica_2.gif", "http://w20.bcn.cat/GuiaMap/img/escala_grafica_3.gif", "http://w20.bcn.cat/GuiaMap/img/escala_grafica_4.gif", "http://w20.bcn.cat/GuiaMap/img/escala_grafica_5.gif", "http://w20.bcn.cat/GuiaMap/img/escala_grafica_6.gif", "http://w20.bcn.cat/GuiaMap/img/escala_grafica_7.gif", "http://w20.bcn.cat/GuiaMap/img/escala_grafica_8.gif"],
            iconOffset: 12,
            WindowWidth: 0,
            WindowHeight: 0,
            MinWidth: 800,
            MinHeight: 500,
            Width: null,
            Height: null,
            ContadorTimeout: 0,
            IsHistoryAction: false,
            x: "27601.010",
            y: "83987.710",
            z: "0",
            capas: "",
            plot: "",
            Callback_Equips: k,
            Callback_Resize: function() {},
            Callback_PageLoad: function() {},
            buttonsLeft: null,
            buttonsRight: null
        };
        buttons = {
            isButtonsLeft: false,
            isButtonsRight: false
        };
        if (G != null) {
            if (G.buttonsLeft != null) {
                buttons.isButtonsLeft = true;
            }
            if (G.buttonsRight != null) {
                buttons.isButtonsRight = true;
            }
        }
        var e = a.extend(defaults, G, buttons);
        e.centroUTMX = e.x * 1000;
        e.centroUTMY = e.y * 1000;
        Mapa = a("<img />").addClass("Mapa").attr({
            alt: "Mapa",
            src: "http://w20.bcn.cat/GuiaMap/img/blanco.gif",
            title: ""
        });
        CentroMapa = a("<img />").addClass("CentroMapa").attr({
            alt: "Centre mapa",
            src: "http://w20.bcn.cat/GuiaMap/img/cruz.gif"
        });
        Progress = a("<img />").addClass("Progress").attr({
            alt: "Actualizant...",
            src: "http://w20.bcn.cat/GuiaMap/img/loading.gif"
        });
        if (e.ShowDesplazamiento || e.ShowSlider || e.isButtonsLeft) {
            Navegacion = a("<div />").addClass("Navegacion");
        }
        if (e.ShowDesplazamiento) {
            Desplazamiento = a("<div />").addClass("Desplazamiento");
        }
        if (e.ShowSlider) {
            Slider = a("<div />").addClass("Slider");
            SliderBar = a("<div />").css("z-index", 9).slider({
                orientation: "vertical",
                range: "min",
                min: e.minzoom,
                max: e.maxzoom,
                value: e.z,
                stop: r
            });
        }
        if (e.isButtonsLeft) {
            ButtonsLeft = a('<div id="buttonsLeft" />');
            a.each(e.buttonsLeft, function() {
                ButtonsLeft.append(a("<img />").attr({
                    src: "img/" + this.icon
                }).click(this.click));
            });
        }
        if (e.isButtonsRight) {
            ButtonsRight = a('<div id="buttonsRight" />');
            a.each(e.buttonsRight, function() {
                icon = this.icon;
                hover = this.hover;
                ButtonsRight.append(a("<div />").css({
                    "background-image": 'url("img/' + icon + '")'
                }).click(this.click).mouseover(function() {
                    a(this).css({
                        "background-image": 'url("img/' + hover + '")'
                    });
                }).mouseout(function() {
                    a(this).css({
                        "background-image": 'url("img/' + icon + '")'
                    });
                }));
            });
        }
        if (e.ShowMapaSituacio) {
            MapaSituacio = a("<div />").addClass("MapaSituacio");
            Mapeta = a("<img />").addClass("Mapeta").attr({
                alt: "Mapeta de situaci??",
                src: "http://w20.bcn.cat/GuiaMap/img/Mapeta.gif"
            }).click(w);
            PuntMapaSituacio = a("<img />").addClass("PuntMapaSituacio").attr({
                alt: "",
                src: "http://w20.bcn.cat/GuiaMap/img/1pxtrans.gif"
            }).draggable({
                start: function(M, o) {
                    a(this).addClass("PuntMapaSituacioCursorMove");
                },
                stop: function(o, M) {
                    t(M);
                    a(this).removeClass("PuntMapaSituacioCursorMove");
                }
            });
            ImgBotoMapaSituacio = a("<img />").addClass("ImgBotoMapaSituacio").attr({
                alt: "MDesplegar/replegar mapeta de situaci??",
                src: "http://w20.bcn.cat/GuiaMap/img/situacio_off.gif"
            }).click(m);
        }
        if (e.ShowImgEscala) {
            EscalaGrafica = a("<div />").addClass("EscalaGrafica");
            ImgRosaVents = a("<img />").addClass("ImgRosaVents").attr({
                alt: "Rosa dels vents",
                src: "http://w20.bcn.cat/GuiaMap/img/rosa.png"
            });
            ImgEscala = a("<img />").addClass("ImgEscala").attr({
                alt: "Escala gr? fica",
                src: "http://w20.bcn.cat/GuiaMap/img/escala_grafica_1.gif"
            });
        }
        ImgCopyright = a("<img />").addClass("ImgCopyright").attr({
            alt: "Copyright Ajuntament de Barcelona",
            src: "http://w20.bcn.cat/GuiaMap/img/copyright_cat.gif"
        }).fancybox({
            type: "iframe",
            href: "http://www.bcn.cat/catala/copyright/",
            width: 778,
            height: 375,
            padding: 0,
            overlayOpacity: 0.8,
            overlayColor: "#848383",
            scrolling: "no",
            transitionIn: "elastic",
            transitionOut: "elastic",
            titleShow: false,
            centerOnScroll: true
        });
        CapasInfoGuia = a("<ul />").attr({
            id: "CapasInfoGuia" + e.IdMap
        });
        CapasInfoUsuario = a("<ul />").attr({
            id: "CapasInfoUsuario" + e.IdMap
        });
        function n(o) {
            if (o === "") {
                return;
            } else {
                if (o === e.prevHash) {
                    return;
                }
                e.prevHash = o;
                e.IsHistoryAction = true;
                C(o);
                e.Callback_PageLoad(e.capas);
                e.IsHistoryAction = false;
            }
        }
        function C(o) {
            if ((o === "") || (o === undefined)) {
                return;
            }
            var O = o.split("&");
            for (var N = 0; N < O.length; N++) {
                var M = O[N].charAt(0);
                switch (M) {
                case "x":
                    e.x = O[N].substr(O[N].indexOf("=") + 1);
                    break;
                case "y":
                    e.y = O[N].substr(O[N].indexOf("=") + 1);
                    break;
                case "z":
                    e.z = O[N].substr(O[N].indexOf("=") + 1);
                    break;
                case "c":
                    e.capas = O[N].substr(O[N].indexOf("=") + 1);
                    break;
                case "p":
                    e.plot = O[N].substr(O[N].indexOf("=") + 1);
                    break;
                }
            }
        }
        function g() {
            CapasInfoUsuario.find("li").find("div").eq(0).each(function() {
                var Q = a(this).attr("class");
                var O = Q.indexOf("xy");
                if (O !== -1) {
                    var o = Q.substr(O + 2, 16);
                    var R = parseInt("0" + o.substr(0, 8), 10);
                    var N = parseInt("0" + o.substr(8, 8), 10);
                    if ((R === e.centroUTMX) && (N === e.centroUTMY)) {
                        return;
                    }
                    var P = l(R, N);
                    P.x -= e.centroGuiaX;
                    P.y -= e.centroGuiaY;
                    var S = Math.round(Mapa.outerWidth() / 2);
                    var M = Math.round(Mapa.outerHeight() / 2);
                    P.x = S + Math.round(P.x / e.escala[e.z]);
                    P.y = M - Math.round(P.y / e.escala[e.z]);
                    a(this).css({
                        left: (P.x - e.iconOffset) + "px",
                        top: (P.y - e.iconOffset) + "px"
                    });
                }
            });
        }
        function l(O, N) {
            var M = 0.713643022094683,
            o = -0.700509555263572,
            Q = 0,
            R = 0,
            P = 0,
            S = 0;
            Q = O - e.centroUTMX;
            R = N - e.centroUTMY;
            P = (Q * M) - (R * o);
            S = (R * M) + (Q * o);
            P += e.centroGuiaX;
            S += e.centroGuiaY;
            return {
                x: P,
                y: S
            };
        }
        function E(N, Q) {
            var P = 0.713643022094683,
            o = 0.700509555263572,
            T = 0,
            U = 0,
            R = 0,
            M = 0,
            O = 0,
            S = 0;
            T = N - e.centroGuiaX;
            U = Q - e.centroGuiaY;
            O = (T * P) - (U * o);
            S = (U * P) + (T * o);
            R = O + e.centroUTMX;
            M = S + e.centroUTMY;
            return {
                x: R,
                y: M
            };
        }
        function y() {
            var M = me.outerWidth();
            var N = me.outerHeight();
            e.centroUTMX = e.x * 1000;
            e.centroUTMY = e.y * 1000;
            e.queryMapaParams = "x=" + e.x;
            e.queryMapaParams += "&y=" + e.y;
            e.queryMapaParams += "&z=" + e.z;
            if (e.capas !== "") {
                e.queryMapaParams += "&c=" + e.capas;
            }
            e.queryMapaParams += "&w=" + (M - 4);
            e.queryMapaParams += "&h=" + (N - 4);
            if (e.plot !== "") {
                e.queryMapaParams += "&p=" + e.plot;
            }
            if (e.queryMapaParams === e.prevQueryMapaParams) {
                return;
            }
            if ((e.UseHistory) && (!e.IsHistoryAction)) {
                a.history.load(e.queryMapaParams);
            }
            e.prevQueryMapaParams = e.queryMapaParams;
            p();
            CapasInfoGuia.html("");
            if (e.capas !== "") {
                var o = "CodiCapa=" + e.capas + "&ImgWidth=" + M + "&ImgHeight=" + N + "&Zoom=" + e.z + "&CentroX=" + Math.round(e.centroUTMX) + "&CentroY=" + Math.round(e.centroUTMY) + "&Idioma=0";
                a.ajax({
                    type: "POST",
                    url: e.queryWS,
                    data: o,
                    dataType: "jsonp",
                    beforeSend: function() {
                        if (Progress.css("display") != "inline") {
                            Progress.show();
                        }
                        if (Mapa.hasClass("MapaCursorMove")) {
                            Mapa.removeClass("MapaCursorMove");
                        }
                        if (!Mapa.hasClass("MapaCursorWait")) {
                            Mapa.addClass("MapaCursorWait");
                        }
                        window.status = "Procesant dades...";
                    },
                    error: function() {
                        Progress.hide();
                        alert("Servei no disponible, provi m?©s tard.");
                    },
                    success: function(O) {
                        e.Callback_Equips(O, e.iconOffset, e.z);
                    },
                    complete: function() {
                        Progress.hide();
                    }
                });
            } else {
                Progress.hide();
            }
            if (Mapa.hasClass("MapaCursorWait")) {
                Mapa.removeClass("MapaCursorWait");
            }
            if (e.ShowMapaSituacio) {
                b(e.centroUTMX, e.centroUTMY, M, N);
            }
        }
        function k(ae, al, T) {
            var aj,
            ag,
            R,
            S,
            ak,
            o = -100,
            U = -100,
            af = null,
            ac = "",
            ab = "",
            ad,
            Q = function() {
                iconOver(this);
                return false;
            },
            M = function() {
                iconOut(this);
                return false;
            };
            window.status = "Procesant dades...";
            a("#CapasInfoGuia").html("");
            if (T > 4) {
                ad = al;
            } else {
                ad = Math.round(al * 0.666);
            }
            for (var W = 0; W < ae.length; W++) {
                var aa,
                ai,
                P,
                O;
                aj = ae[W].C;
                ag = ae[W].N;
                R = ae[W].X;
                S = ae[W].Y;
                ak = ae[W].Id;
                ag = ag.replace(/ #/, "");
                var ah = ae[W].NC;
                if ((R !== o) || (S !== U)) {
                    aa = document.createElement("li");
                    ai = document.createElement("a");
                    P = document.createElement("span");
                    O = "";
                    a(P).addClass("info");
                    if (ak.indexOf("ASIA") >= 0) {
                        O = e.queryEQ + ak.substr(ak.indexOf("ASIA") + 4) + "&idioma=" + a("html").attr("lang");
                    } else {
                        if (ak.indexOf("OBRA") >= 0) {
                            O = queryOB + ak.substr(ak.indexOf("OBRA") + 4) + "&idioma=" + a("html").attr("lang");
                        } else {
                            if (ak.indexOf("URL") >= 0) {
                                O = ak.substr(ak.indexOf("URL") + 3);
                            } else {
                                O = e.queryEQs + "?idioma=" + a("html").attr("lang") + "&ID=" + ak;
                            }
                        }
                    }
                    if (ag.match(/<br>/i)) {
                        ag = ag.replace(/<br>/i, "</strong><br>");
                    } else {
                        ag = ag + "</strong>";
                    }
                    ag = "<i>" + ah + "</i><br><strong>" + ag;
                    P.innerHTML = ag;
                    ai.appendChild(P);
                    aa.appendChild(ai);
                    a("#CapasInfoGuia").append(aa);
                    ai.onmouseover = Q;
                    ai.onmouseout = M;
                    af = P;
                    ac = aj;
                    ab = ak;
                } else {
                    var V = af.innerHTML + "<hr>";
                    ag = "<strong>" + ag;
                    if (ag.match(/<br>/i)) {
                        ag = ag.replace(/<br>/i, "</strong><br>");
                    } else {
                        ag = ag + "</strong>";
                    }
                    if (aj !== ac) {
                        ag = "<i>" + ah + "</i><br>" + ag;
                        ac = aj;
                    }
                    af.innerHTML = V + ag;
                    ab = ab + ";" + ak;
                }
                if (ab.indexOf(";") > 0) {
                    O = e.queryEQs + "?idioma=" + a("html").attr("lang") + "&ID=" + ab;
                    ai.setAttribute("href", "");
                }
                ai.setAttribute("href", O);
                ai.setAttribute("id", ak);
                ai.style.position = "absolute";
                ai.style.left = (R - ad) + "px";
                ai.style.top = (S - ad) + "px";
                ai.style.width = (ad * 2) + "px";
                ai.style.height = (ad * 2) + "px";
                ai.style.zindex = 5;
                o = R;
                U = S;
            }
            a("#CapasInfoGuia A").mouseover(function() {
                iconOver(this);
            }).mouseout(function() {
                iconOut(this);
            });
            a("#CapasInfoGuia A").addClass("LinkEquips").css("cursor", "pointer");
            if (e.ShowPopUpLinks) {
                a("#CapasInfoGuia A").fancybox({
                    type: "iframe",
                    autoDimensions: false,
                    width: 680,
                    height: 500,
                    padding: 0,
                    overlayOpacity: 0.8,
                    overlayColor: "#848383",
                    transitionIn: "elastic",
                    transitionOut: "elastic",
                    titleShow: false,
                    centerOnScroll: true
                });
            } else {
                a("#CapasInfoGuia A").attr("target", "_blank");
            }
            window.status = "Proc?©s acabat.";
        }
        function B(M) {
            a(M).append('<span class="sombraH"></span><span class="sombraV"></span><span class="sombraV2"></span><span class="punta"></span>');
            var U = a(M).parents(".ContenedorMapa").width();
            var Q = a(M).parents(".ContenedorMapa").height();
            var O = M.offsetLeft;
            var N = M.offsetTop;
            var R = 30;
            var T = a(M).children("span.info").height();
            var S = 140;
            var V = T + a(M).height();
            if ((O + S + R) <= U) {
                if ((V + R) > N) {
                    var o = 17;
                    var P = 17;
                    a(M).children("span.punta").css({
                        background: "url(http://www.bcn.cat/planol_bcn/img/bubble/punta1.png) 0 0 no-repeat",
                        margin: o + "px 0 0 " + P + "px"
                    });
                    a(M).children("span.info").css({
                        margin: (o + 22) + "px 0 0 " + (P + 8) + "px"
                    });
                    a(M).children("div#FondoDireccionActual").css({
                        margin: (o + 22) + "px 0 0 " + (P + 8) + "px"
                    });
                    a(M).children("span.sombraH").css({
                        "margin-top": (o + T + 44) + "px",
                        "margin-left": P + "px"
                    });
                    a(M).children("span.sombraV").css({
                        "margin-top": (o + 34) + "px",
                        "margin-left": P + "px",
                        height: (T + 10)
                        });
                    a(M).children("span.sombraV2").css({
                        "margin-top": (o + 24) + "px",
                        "margin-left": P + "px"
                    });
                } else {
                    var o = -18;
                    var P = 18;
                    a(M).children("span.punta").css({
                        background: "url(http://www.bcn.cat/planol_bcn/img/bubble/punta3.png) 0 0 no-repeat",
                        margin: o + "px 0 0 " + P + "px"
                    });
                    a(M).children("span.info").css({
                        margin: (o - T - 21) + "px 0 0 " + (P + 8) + "px"
                    });
                    a(M).children("div#FondoDireccionActual").css({
                        margin: (o - T - 21) + "px 0 0 " + (P + 8) + "px"
                    });
                    a(M).children("span.sombraH").css({
                        "margin-top": (o + 1) + "px",
                        "margin-left": P + "px"
                    });
                    a(M).children("span.sombraV").css({
                        margin: (o - T - 9) + "px 0 0 " + P + "px",
                        height: (T + 10)
                        });
                    a(M).children("span.sombraV2").css({
                        "margin-top": (o - T - 19) + "px",
                        "margin-left": P + "px"
                    });
                }
            } else {
                if ((V + R) > N) {
                    var o = 18;
                    var P = -157;
                    a(M).children("span.punta").css({
                        background: "url(http://www.bcn.cat/planol_bcn/img/bubble/punta2.png) 0 0 no-repeat",
                        margin: o + "px 0 0 " + (P + 122) + "px"
                    });
                    a(M).children("span.info").css({
                        margin: (o + 22) + "px 0 0 " + (P + 8) + "px"
                    });
                    a(M).children("div#FondoDireccionActual").css({
                        margin: (o + 22) + "px 0 0 " + (P + 8) + "px"
                    });
                    a(M).children("span.sombraH").css({
                        margin: (o + T + 44) + "px 0 0 " + P + "px"
                    });
                    a(M).children("span.sombraV").css({
                        "margin-top": (o + 34) + "px",
                        "margin-left": P + "px",
                        height: (T + 10)
                        });
                    a(M).children("span.sombraV2").css({
                        "margin-top": (o + 24) + "px",
                        "margin-left": P + "px"
                    });
                } else {
                    var o = -17;
                    var P = -155;
                    a(M).children("span.punta").css({
                        background: "url(http://www.bcn.cat/planol_bcn/img/bubble/punta4.png) 0 0 no-repeat",
                        margin: o + "px 0 0 " + (P + 113) + "px"
                    });
                    a(M).children("span.info").css({
                        margin: (o - T - 21) + "px 0 0 " + (P + 8) + "px"
                    });
                    a(M).children("div#FondoDireccionActual").css({
                        margin: (o - T - 21) + "px 0 0 " + (P + 8) + "px"
                    });
                    a(M).children("span.sombraH").css({
                        margin: (o + 1) + "px 0 0 " + P + "px"
                    });
                    a(M).children("span.sombraV").css({
                        margin: (o - T - 9) + "px 0 0 " + P + "px",
                        height: (T + 10)
                        });
                    a(M).children("span.sombraV2").css({
                        "margin-top": (o - T - 19) + "px",
                        "margin-left": P + "px"
                    });
                }
            }
            a(M).pngFix();
        }
        function q() {
            if (e.Height != null) {
                height_tmp = e.Height;
            } else {
                height_tmp = a(window).height() - me.parents("div").offset().top;
                parentsel = me.parent("div");
                while (parentsel.exists()) {
                    if (parentsel.is(":visible")) {
                        height_tmp -= A(parentsel.css("marginBottom"));
                        height_tmp -= A(parentsel.css("paddingBottom"));
                    }
                    parentsel = parentsel.parent("div");
                }
                height_tmp -= A(me.css("borderBottomWidth"));
                parentsel = me.parent("div");
                while (parentsel.exists()) {
                    parentsel2 = parentsel.next("div");
                    while (parentsel2.exists()) {
                        if (parentsel2.is(":visible")) {
                            height_tmp -= parentsel2.outerHeight();
                        }
                        parentsel2 = parentsel2.next("div");
                    }
                    parentsel = parentsel.parent("div");
                }
            }
            return height_tmp;
        }
        function x() {
            if (e.Width != null) {
                width_tmp = e.Width;
            } else {
                width_tmp = a(window).width() - me.offset().left;
                parentsel = me.parent("div");
                while (parentsel.exists()) {
                    if (parentsel.is(":visible")) {
                        width_tmp -= A(parentsel.css("marginRight"));
                        width_tmp -= A(parentsel.css("paddingRight"));
                    }
                    parentsel = parentsel.parent("div");
                }
                width_tmp += A(me.css("borderRightWidth"));
            }
            return width_tmp;
        }
        function A(o) {
            value_extract = parseInt(o);
            if (isNaN(value_extract)) {
                value_extract = 0;
            }
            return value_extract;
        }
        function L(O, N) {
            e.Callback_Resize(N);
            me.height(N - 1);
            if (e.Width != null) {
                me.width(O - 1);
            }
            var Q = A(CentroMapa.css("left"));
            var P = A(CentroMapa.css("top"));
            CentroMapa.css({
                left: Math.round((me.outerWidth() / 2) - (CentroMapa.outerWidth() / 2)) + "px",
                top: Math.round((me.outerHeight() / 2) - (CentroMapa.outerHeight() / 2)) + "px"
            });
            Progress.css({
                left: Math.round((me.outerWidth() / 2) - (Progress.outerWidth() / 2)) + "px",
                top: Math.round((me.outerHeight() / 2) - (Progress.outerHeight() / 2)) + "px"
            });
            if (e.ShowMapaSituacio) {
                f();
            }
            y();
            var o = ((e.WindowWidth - O) / 2);
            var M = ((e.WindowHeight - N) / 2);
            D(o, M);
        }
        function D(M, o) {
            CapasInfoUsuario.find("li").find("div:eq(0)").each(function() {
                var O = A(a(this).css("left")) - M + 0.3;
                var N = A(a(this).css("top")) - o + 0.5;
                a(this).css({
                    left: O + "px",
                    top: N + "px"
                });
            });
        }
        function p() {
            var o = e.queryMapa + e.queryMapaParams,
            N = A(Mapa.css("left"), 10),
            M = A(Mapa.css("top"), 10);
            if ((N === 1) && (M === 1)) {
                Mapa.attr("src", o);
            } else {
                if (!Mapa.hasClass("MapaCursorWait")) {
                    Mapa.addClass("MapaCursorWait");
                }
                Mapa.after(a("<img />").css({
                    width: Mapa.width(),
                    height: Mapa.height(),
                    position: "absolute",
                    cursor: "wait",
                    left: "1px",
                    top: "1px",
                    overflow: "hidden"
                }).attr({
                    id: "TmpImg" + e.IdMap,
                    alt: "Mapa",
                    title: "",
                    src: o
                }).show());
                me.find("#TmpImg" + e.IdMap).load(function() {
                    Mapa.attr("src", o);
                });
                Mapa.load(function() {
                    a(this).css({
                        left: "1px",
                        top: "1px"
                    });
                    me.find("#TmpImg" + e.IdMap).remove();
                });
            }
            if (e.ShowImgEscala) {
                ImgEscala.attr("src", e.escala_grafica[e.z]);
            }
        }
        function z() {
            CapasInfoGuia.hide();
            CapasInfoUsuario.hide();
        }
        function J() {
            CapasInfoGuia.show();
            CapasInfoUsuario.show();
        }
        function h(M, o) {
            var N;
            if ((M !== 0) || (o !== 0)) {
                M *= e.escala[e.z];
                o *= e.escala[e.z];
                guiaX = e.centroGuiaX - M;
                guiaY = e.centroGuiaY + o;
                N = E(guiaX, guiaY);
                e.centroGuiaX = guiaX;
                e.centroGuiaY = guiaY;
                e.centroUTMX = N.x;
                e.centroUTMY = N.y;
                e.x = Math.round(N.x / 1000);
                e.y = Math.round(N.y / 1000);
                UTMX = N.x;
                UTMY = N.y;
                g();
                y();
            }
            J();
            return false;
        }
        function d() {
            if (e.z < e.maxzoom) {
                e.z++;
            }
            e.centroUTMX = UTMX;
            e.centroUTMY = UTMY;
            e.centroGuiaX = guiaX;
            e.centroGuiaY = guiaY;
            e.x = UTMX / 1000;
            e.y = UTMY / 1000;
            F();
            v(UTMX, UTMY);
            return true;
        }
        function H(O) {
            var N,
            M,
            o,
            P,
            Q;
            if (O) {
                N = O.target;
                imgX = O.pageX;
                imgY = O.pageY;
                imgX = imgX - N.offsetLeft;
                imgY = imgY - N.offsetTop;
                P = N.offsetParent;
                while (P !== null) {
                    imgX -= P.offsetLeft;
                    imgY -= P.offsetTop;
                    P = P.offsetParent;
                }
            } else {
                N = event.srcElement;
                imgX = event.x;
                imgY = event.y;
            }
            M = N.width;
            o = N.height;
            imgX = imgX - N.border;
            imgY = imgY - N.border;
            mouseX = imgX - (M / 2);
            mouseY = -(imgY - (o / 2));
            guiaX = e.centroGuiaX + (mouseX * e.escala[e.z]);
            guiaY = e.centroGuiaY + (mouseY * e.escala[e.z]);
            guiaX = Math.round(guiaX);
            guiaY = Math.round(guiaY);
            Q = E(guiaX, guiaY);
            UTMX = Math.round(Q.x);
            UTMY = Math.round(Q.y);
            v(UTMX, UTMY);
            return true;
        }
        function v(N, M) {
            var o = (N / 1000) + 400000;
            var O = (M / 1000) + 4500000;
            var P = c(o, O);
            var Q = "(" + imgX + "," + imgY + ") Coords. UTM ED50: (H31) " + o.toFixed(2) + "," + O.toFixed(2);
            Q += " - Geo: " + P;
            window.status = Q;
        }
        function c(o, M) {
            var ax,
            al,
            ad,
            ai,
            am,
            Q,
            aE,
            R,
            at,
            ae,
            V,
            aq,
            ao,
            an,
            aF,
            aD,
            aC,
            W,
            ah,
            U,
            ag,
            ac,
            av,
            af,
            aA,
            aB,
            aw,
            ak,
            P;
            var az,
            ab,
            ay;
            var T = "",
            O = "";
            var N = 0,
            aj = 0,
            ar = -131.250417839,
            aa = -206.9696618318,
            au = (1.321908127 / 1000000),
            Z = ( - 1.6446198 / 3600) * Math.PI / 180,
            S = Math.sin(Z),
            ap = Math.cos(Z);
            N = ar + ((1 + au) * ((o * ap) - (M * S)));
            aj = aa + ((1 + au) * ((o * S) + (M * ap)));
            ax = 6378137;
            al = 6356752.31414035;
            ad = (Math.pow((Math.pow(ax, 2) - Math.pow(al, 2)), 0.5)) / (al);
            ai = Math.pow(ad, 2);
            am = Math.pow(ax, 2) / al;
            ac = N - 500000;
            av = aj;
            R = (31 * 6) - 183;
            aE = av / (6366197.724 * 0.9996);
            aq = am * 0.9996 / Math.pow((1 + ai * Math.pow(Math.cos(aE), 2)), 0.5);
            ax = ac / aq;
            an = Math.sin(2 * aE);
            aF = an * Math.pow(Math.cos(aE), 2);
            aD = aE + (an / 2);
            aC = ((3 * aD) + aF) / 4;
            W = ((5 * aC) + aF * Math.pow(Math.cos(aE), 2)) / 3;
            Q = 3 * ai / 4;
            ah = 5 * Math.pow(Q, 2) / 3;
            U = 35 * Math.pow(Q, 3) / 27;
            ag = 0.9996 * am * (aE - Q * aD + ah * aC - U * W);
            al = (av - ag) / aq;
            ao = (ai * Math.pow(ax, 2) * Math.pow(Math.cos(aE), 2)) / 2;
            ae = ax * (1 - (ao / 3));
            V = al * (1 - ao) + aE;
            af = Math.exp(1);
            aA = (Math.pow(af, ae) - Math.pow(af, -ae)) / 2;
            at = Math.atan(aA / Math.cos(V));
            aB = Math.atan(Math.cos(at) * Math.tan(V));
            ak = ((at / Math.PI) * 180) + R;
            aw = aE + (((1 + (ai * Math.pow(Math.cos(aE), 2)) - (3 / 2 * ai * Math.sin(aE) * Math.cos(aE) * (aB - aE)))) * (aB - aE));
            P = (aw / Math.PI) * 180;
            az = Math.floor(ak);
            ab = Math.floor((ak - az) * 60);
            ay = (((ak - az) * 60) - ab) * 60;
            T = az + "?? " + ab + "' " + ay.toFixed(4) + '" E';
            az = Math.floor(P);
            ab = Math.floor((P - az) * 60);
            ay = (((P - az) * 60) - ab) * 60;
            O = az + "?? " + ab + "' " + ay.toFixed(4) + '" N';
            return O + ", " + T;
        }
        function i(o) {
            if (o > 0) {
                if (e.z < e.maxzoom) {
                    e.z++;
                    F();
                }
            } else {
                if (e.z > e.minzoom) {
                    e.z--;
                    F();
                }
            }
        }
        function F() {
            Progress.show();
            if (!Mapa.hasClass("MapaCursorWait")) {
                Mapa.addClass("MapaCursorWait");
            }
            if (e.ShowSlider) {
                SliderBar.slider("value", e.z);
            }
            s();
        }
        function j(S) {
            if (me.find("#TmpImg" + e.IdMap).exists()) {
                return;
            }
            Progress.show();
            if (!Mapa.hasClass("MapaCursorWait")) {
                Mapa.addClass("MapaCursorWait");
            }
            var O = me.outerWidth();
            var M = me.outerHeight();
            var o = O * e.escala[e.z];
            var P = M * e.escala[e.z];
            var Q = l(e.x * 1000, e.y * 1000);
            var N = 0,
            T = 0;
            z();
            switch (S) {
            case "up":
                Q.y += Math.round(P / 2);
                T += Math.round(M / 2);
                break;
            case "down":
                Q.y -= Math.round(P / 2);
                T -= Math.round(M / 2);
                break;
            case "left":
                Q.x -= Math.round(o / 2);
                N += Math.round(O / 2);
                break;
            case "right":
                Q.x += Math.round(o / 2);
                N -= Math.round(O / 2);
                break;
            }
            var R = E(Q.x, Q.y);
            e.centroGuiaX = Q.x;
            e.centroGuiaY = Q.y;
            e.centroUTMX = R.x;
            e.centroUTMY = R.y;
            UTMX = Math.round(R.x);
            UTMY = Math.round(R.y);
            e.x = Math.round(UTMX / 1000);
            e.y = Math.round(UTMY / 1000);
            if (e.ShowMapaSituacio) {
                b(e.centroUTMX, e.centroUTMY, O, M);
            }
            Mapa.animate({
                left: "+=" + N,
                top: "+=" + T
            }, 250, function() {
                y();
                J();
            });
        }
        function r(M, o) {
            if (e.IsHistoryAction) {
                return;
            }
            Progress.show();
            if (!Mapa.hasClass("MapaCursorWait")) {
                Mapa.addClass("MapaCursorWait");
            }
            e.z = o.value;
            s();
        }
        function s() {
            e.ContadorTimeout++;
            setTimeout(K, 200);
        }
        function K() {
            e.ContadorTimeout--;
            if (e.ContadorTimeout === 0) {
                y();
                g();
            }
        }
        function f() {
            ButtonsTop = 0;
            if (e.isButtonsRight) {
                ButtonsTop = e.buttonsRight.length * 25;
            }
            if (MapaSituacio.hasClass("visible")) {
                MapaSituacio.css({
                    top: (ButtonsTop + 9) + "px",
                    width: "200px",
                    height: "150px",
                    zindex: 10,
                    border: "1px solid",
                    backgroundImage: "url(http://w20.bcn.cat/GuiaMap/img/Mapeta.gif)"
                });
                Mapeta.show();
                ImgBotoMapaSituacio.css({
                    top: "124px",
                    cursor: "pointer"
                }).attr("src", "http://w20.bcn.cat/GuiaMap/img/situacio_on.gif").mouseover(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/situacio_on_2.gif");
                }).mouseout(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/situacio_on.gif");
                });
            } else {
                MapaSituacio.css({
                    top: (ButtonsTop + 9) + "px",
                    width: "26px",
                    height: "26px",
                    border: "none",
                    backgroundImage: "none"
                });
                Mapeta.hide();
                ImgBotoMapaSituacio.css({
                    top: 0,
                    cursor: "pointer"
                }).attr("src", "http://w20.bcn.cat/GuiaMap/img/situacio_off.gif").mouseover(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/situacio_off_2.gif");
                }).mouseout(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/situacio_off.gif");
                });
            }
            //ELAZOS MapaSituacio.pngFix();
        }
        function m() {
            if (MapaSituacio.hasClass("visible")) {
                PuntMapaSituacio.hide();
                Mapeta.hide();
                ImgBotoMapaSituacio.mouseover(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/situacio_off_2.gif");
                }).mouseout(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/situacio_off.gif");
                }).attr("src", "http://w20.bcn.cat/GuiaMap/img/situacio_off.gif");
                MapaSituacio.animate({
                    width: "26px",
                    height: "26px"
                }, 500, function() {
                    ImgBotoMapaSituacio.css("top", 0);
                    a(this).css({
                        backgroundImage: "none",
                        border: "none"
                    });
                }).removeClass("visible");
                I("Mapeta", "", -1);
            } else {
                PuntMapaSituacio.show();
                Mapeta.show();
                ImgBotoMapaSituacio.css("top", "124px").mouseover(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/situacio_on_2.gif");
                }).mouseout(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/situacio_on.gif");
                }).attr("src", "http://w20.bcn.cat/GuiaMap/img/situacio_on.gif");
                MapaSituacio.css({
                    border: "1px solid",
                    backgroundImage: "url(http://w20.bcn.cat/GuiaMap/img/Mapeta.gif)",
                    backgroundPosition: "left top"
                }).animate({
                    width: "200px",
                    height: "150px"
                }, 500).addClass("visible");
                I("Mapeta", true, 365);
            }
            MapaSituacio.pngFix();
        }
        function I(o, P, O) {
            if (O) {
                var M = new Date();
                M.setTime(M.getTime() + (O * 24 * 60 * 60 * 1000));
                var N = "; expires=" + M.toGMTString();
            } else {
                N = "";
            }
            document.cookie = o + "=" + P + N + "; path=/";
        }
        function b(X, W, U, T) {
            var Y = 27601103,
            V = 83987710,
            o = 0,
            P = 0,
            R,
            N,
            S = -0.700509,
            Q = 0.713643,
            M,
            O;
            U *= e.escala[e.z];
            T *= e.escala[e.z];
            U /= 128000;
            T /= 128000;
            R = (X - Y) / 128000;
            N = (W - V) / 128000;
            o = (R * Q) - (N * S);
            P = (N * Q) + (R * S);
            o += 100;
            P = 150 - (P + 75);
            o -= 2;
            P -= 2;
            M = Math.round(o - (U / 2));
            O = Math.round(P - (T / 2));
            PuntMapaSituacio.css({
                left: M + "px",
                top: O + "px",
                width: U + "px",
                height: T + "px"
            });
        }
        function t(M) {
            var o = M.position.left;
            var P = M.position.top;
            var N = Math.round(PuntMapaSituacio.outerWidth() / 2);
            var O = Math.round(PuntMapaSituacio.outerHeight() / 2);
            o += N;
            P += O;
            u(o, P);
        }
        function w(M) {
            var o = M.pageX - Mapeta.parents().offset().left;
            var N = M.pageY - Mapeta.parents().offset().top;
            u(o, N);
        }
        function u(P, o) {
            var S = 27601103,
            R = 83987710,
            N,
            M,
            Q = 0.700509,
            O = 0.713643;
            P -= 100;
            o = 150 - (o + 75);
            N = (P * O) - (o * Q);
            M = (o * O) + (P * Q);
            N *= 128000;
            M *= 128000;
            N += S;
            M += R;
            e.x = N / 1000;
            e.y = M / 1000;
            e.centroUTMX = e.x;
            e.centroUTMY = e.y;
            Progress.show();
            y();
        }
        el.build = function() {
            if (e.UseHistory) {
                a.history.init(n);
            }
            if (e.DragMap) {
                Mapa.addClass("MapaMove").draggable({
                    start: function(M, o) {
                        CentroMapa.show();
                        if (!a(this).hasClass("MapaCursorMove")) {
                            a(this).addClass("MapaCursorMove");
                        }
                    },
                    drag: z,
                    stop: function(M, o) {
                        var O,
                        N;
                        CentroMapa.hide();
                        O = A(a(this).css("left"), 10);
                        N = A(a(this).css("top"), 10);
                        Progress.show();
                        if (a(this).hasClass("MapaCursorMove")) {
                            a(this).removeClass("MapaCursorMove");
                        }
                        if (!a(this).hasClass("MapaCursorWait")) {
                            a(this).addClass("MapaCursorWait");
                        }
                        h(O, N);
                    }
                });
            }
            if (e.ZoomDoubleClick) {
                Mapa.dblclick(d);
            }
            if (e.ShowStatusCoords) {
                Mapa.mousemove(function(o) {
                    H(o);
                });
            }
            if (e.ZoomMouse) {
                Mapa.mousewheel(function(o, M) {
                    i(M);
                });
            }
            if (e.ShowDesplazamiento) {
                Desplazamiento.append(a("<img />").attr({
                    alt: "Despla?§ar centre del mapa",
                    src: "http://w20.bcn.cat/GuiaMap/img/moviment_bg.png",
                    height: "73",
                    width: "70"
                })).append(a("<img />").addClass("MoveUp").attr({
                    alt: "Despla?§ar centre del mapa cap a dalt",
                    src: "http://w20.bcn.cat/GuiaMap/img/arrow_up.gif"
                }).mouseout(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/arrow_up.gif");
                }).mouseover(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/arrow_up2.gif");
                }).click(function() {
                    setTimeout(function() {
                        j("up");
                    }, 500);
                })).append(a("<img />").addClass("MoveLeft").attr({
                    alt: "Despla?§ar centre del mapa cap a l'esquerra",
                    src: "http://w20.bcn.cat/GuiaMap/img/arrow_left.gif"
                }).mouseout(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/arrow_left.gif");
                }).mouseover(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/arrow_left2.gif");
                }).click(function() {
                    setTimeout(function() {
                        j("left");
                    }, 500);
                })).append(a("<img />").addClass("MoveRight").attr({
                    alt: "Despla?§ar centre del mapa cap a la dreta",
                    src: "http://w20.bcn.cat/GuiaMap/img/arrow_right.gif"
                }).mouseout(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/arrow_right.gif");
                }).mouseover(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/arrow_right2.gif");
                }).click(function() {
                    setTimeout(function() {
                        j("right");
                    }, 500);
                })).append(a("<img />").addClass("MoveDown").attr({
                    alt: "Despla?§ar centre del mapa cap a baix",
                    src: "http://w20.bcn.cat/GuiaMap/img/arrow_down.gif"
                }).mouseout(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/arrow_down.gif");
                }).mouseover(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/arrow_down2.gif");
                }).click(function() {
                    setTimeout(function() {
                        j("down");
                    }, 500);
                }));
            }
            if (e.ShowSlider) {
                Slider.append(a("<img />").attr({
                    id: "sliderbg" + e.IdMap,
                    alt: "Engrandir l'escala del mapa",
                    src: "http://w20.bcn.cat/GuiaMap/img/bg_escale.png",
                    height: "164",
                    width: "24"
                })).append(a("<img />").addClass("sliderUp").attr({
                    alt: "",
                    src: "http://w20.bcn.cat/GuiaMap/img/SliderUp1.gif",
                    height: "24",
                    width: "24"
                }).mouseout(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/SliderUp1.gif");
                }).mouseover(function() {
                    if (e.z < e.maxzoom) {
                        a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/SliderUp2.gif");
                    }
                }).click(function() {
                    if (e.z < e.maxzoom) {
                        e.z++;
                        F();
                        if (e.z === e.maxzoom) {
                            a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/SliderUp1.gif");
                        }
                    }
                })).append(SliderBar).append(a("<img />").addClass("sliderDown").attr({
                    alt: "Redu??r l'escala del mapa",
                    alt: "",
                    src: "http://w20.bcn.cat/GuiaMap/img/SliderDown1.gif",
                    height: "24",
                    width: "24"
                }).mouseout(function() {
                    a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/SliderDown1.gif");
                }).mouseover(function() {
                    if (e.z > e.minzoom) {
                        a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/SliderDown2.gif");
                    }
                }).click(function() {
                    if (e.z > e.minzoom) {
                        e.z--;
                        F();
                        if (e.z === e.minzoom) {
                            a(this).attr("src", "http://w20.bcn.cat/GuiaMap/img/SliderDown1.gif");
                        }
                    }
                }));
            }
            if (e.ShowDesplazamiento) {
                Navegacion.append(Desplazamiento);
            } else {
                if (e.ShowSlider) {
                    Slider.children("img:eq(1)").css("top", "4px");
                    SliderBar.css("top", "46px");
                    Slider.children("img:eq(2)").css("top", "145px");
                }
            }
            if (e.ShowSlider) {
                Navegacion.append(Slider);
            }
            if (e.isButtonsLeft) {
                Navegacion.append(ButtonsLeft);
            }
            if (e.ShowMapaSituacio) {
                MapaSituacio.append(Mapeta).append(PuntMapaSituacio).append(ImgBotoMapaSituacio);
                if (e.MapaSituacioVisible) {
                    PuntMapaSituacio.show();
                    MapaSituacio.addClass("visible");
                }
            }
            if (e.ShowImgEscala) {
                EscalaGrafica.append(ImgRosaVents).append(ImgEscala);
            }
            ImageMap = a("<div />").attr({
                id: "ImageMap" + e.IdMap
            }).addClass("ImageMap").append(CapasInfoGuia).append(CapasInfoUsuario);
            me.attr({
                "class": "ContenedorMapa"
            }).append(Mapa).append(CentroMapa).append(Progress);
            if (e.ShowDesplazamiento || e.ShowSlider || e.isButtonsLeft) {
                me.append(Navegacion);
            }
            if (e.isButtonsRight) {
                me.append(ButtonsRight);
            }
            if (e.ShowMapaSituacio) {
                me.append(MapaSituacio);
            }
            if (e.ShowImgEscala) {
                me.append(EscalaGrafica);
            }
            me.append(ImgCopyright).append(ImageMap);
            Mapa.removeAttr("width").removeAttr("height");
            if (e.ShowSlider) {
                F();
            }
            el.WResize();
            a(window).resize(el.WResize);
            return this;
        };
        el.WResize = function() {
            var M = x();
            var o = q();
            if ((M !== e.WindowWidth) || (o !== e.WindowHeight)) {
                L(M, o);
            }
            e.WindowWidth = M;
            e.WindowHeight = o;
        };
        el.Resize = function(M, o) {
            me.width(M - 1);
            me.height(o - 1);
            y();
        };
        el.PonCapa = function(o) {
            if (e.capas.indexOf(o) !== -1) {
                return;
            } else {
                e.capas += o;
            }
        };
        el.QuitaCapa = function(o) {
            if (e.capas.indexOf(o) === -1) {
                return;
            } else {
                e.capas = e.capas.replace(o, "");
            }
        };
        el.onCapaTimeout = function() {
            e.ContadorTimeout--;
            if (e.ContadorTimeout === 0) {
                y();
            }
        };
        el.addContadorTimeout = function() {
            e.ContadorTimeout++;
        };
        el.iconOver = function(o) {
            if (!a(o).hasClass("iniciat")) {
                B(o);
                a(o).addClass("iniciat");
            }
            a(o).children("span").css("display", "block");
        };
        el.iconOut = function(o) {
            a(o).children("span").css("display", "none");
        };
        el.setDefaults = function() {
            e.centroUTMX = 27601010;
            e.centroUTMY = 83987710;
            e.centroGuiaX = 11200000;
            e.centroGuiaY = 11200000;
            e.x = "27601.010";
            e.y = "83987.710";
            e.z = "0";
            e.capas = "";
            e.plot = "";
            F();
        };
        el.setCentroUTMX = function(o) {
            e.centroUTMX = o;
            e.x = e.centroUTMX / 1000;
        };
        el.setCentroUTMY = function(o) {
            e.centroUTMY = o;
            e.y = e.centroUTMY / 1000;
        };
        el.setXY = function(o, M) {
            e.x = o;
            e.y = M;
        };
        el.setPlot = function() {
            e.plot = e.x + "," + e.y;
            e.z = 5;
            F();
        };
        el.setWait = function() {
            if (Mapa.hasClass("MapaCursorMove")) {
                Mapa.removeClass("MapaCursorMove");
            }
            if (!Mapa.hasClass("MapaCursorWait")) {
                Mapa.addClass("MapaCursorWait");
            }
        };
        el.setMove = function() {
            Mapa.addClass("MapaMove");
        };
        el.removeCapas = function() {
            e.capas = "";
            y();
        };
        el.getXYZ = function() {
            return e.x + "|" + e.y + "|" + e.z;
        };
        el.getParams = function() {
            var o = "#x=" + e.x;
            o += "&y=" + e.y;
            o += "&z=" + e.z;
            if (e.capas !== "") {
                o += "&c=" + e.capas;
            }
            o += "&w=" + (me.outerWidth() - 4);
            o += "&h=" + (me.outerHeight() - 4);
            if (e.plot !== "") {
                o += "&p=" + e.plot;
            }
            return o;
        };
        el.getCapas = function() {
            return e.capas;
        };
        el.setCapas = function(o) {
            e.capas = o;
            y();
        };
        el.getIconOffset = function() {
            return e.iconOffset;
        };
        el.getOuter = function() {
            return {
                width: Mapa.outerWidth(),
                height: Mapa.outerHeight()
                };
        };
        return el.build();
    };
})(jQuery);