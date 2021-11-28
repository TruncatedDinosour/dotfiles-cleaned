// Autogenerated by `scribblings/main/private/local-redirect'
//  This script is included by generated documentation to rewrite
//  links expressed as tag queries into local-filesystem links.

link_target_prefix = "file:///usr/share/doc/racket-8.2-r1/local-redirect/";

var user_link_dirs = [
 ["fancy-app", "file:///home/ari/.racket/8.2/pkgs/fancy-app/doc/fancy-app"],
 ["http-easy", "file:///home/ari/.racket/8.2/pkgs/http-easy/doc/http-easy"],
 ["memoize", "file:///home/ari/.racket/8.2/pkgs/memoize/memoize/doc/memoize"]];

function user_bsearch(str, a, start, end) {
   if (start >= end)
     return false;
   else {
     var mid = Math.floor((start + end) / 2);
     if (a[mid][0] == str)
       return mid;
     else if (a[mid][0] < str)
       return user_bsearch(str, a, mid+1, end);
     else
       return user_bsearch(str, a, start, mid);
   }
}

var user_link_target_prefix = false;

function hash_string(s) {
   var v = 0;
   for (var i = 0; i < s.length; i++) {
     v = (((v << 5) - v) + s.charCodeAt(i)) & 0xFFFFFF;
   }
   return v;
}

function demand_load(p, callback) {
   // Based on a StackOverflow answer, which cites:
   // JavaScript Patterns, by Stoyan Stefanov (O’Reilly). Copyright 2010 Yahoo!, Inc., 9780596806750.
   var script = document.getElementsByTagName('script')[0];
   var newjs = document.createElement('script');
   newjs.src = p;
   if (callback) {
      // IE
      newjs.onreadystatechange = function () {
          if (newjs.readyState === 'loaded' || newjs.readyState === 'complete') {
            newjs.onreadystatechange = null;
            callback();
          }
        };
      // others
      newjs.onload = callback;
   }
   script.parentNode.appendChild(newjs);
}

var user_loaded_link_targets = [];
var user_link_targets = [];
var user_num_link_target_bins = 1;

function user_convert_all_links() {
   var elements = document.getElementsByClassName("Sq");
   for (var i = 0; i < elements.length; i++) {
     var elem = elements[i];
     var tag = elem.href.match(/tag=[^&]*/);
     var doc = elem.href.match(/doc=[^&]*/);
     var rel = elem.href.match(/rel=[^&]*/);
     if (doc && rel) {
         var pos = user_bsearch(decodeURIComponent(doc[0].substring(4)),
                                     user_link_dirs,
                                     0,
                                     user_link_dirs.length);
         if (pos) {
           var p = user_link_dirs[pos][1];
           if (user_link_target_prefix) {
             p = user_link_target_prefix + p;
           }
           elem.href = p + "/" + decodeURIComponent(rel[0].substring(4));
           tag = false;
         }
     }
     if (tag) {
       var v = hash_string(decodeURIComponent(tag[0].substring(4))) % 1;
       if (!user_loaded_link_targets[v]) {
         user_loaded_link_targets[v] = true;
         var p = "file:///home/ari/.racket/8.2/doc/local-redirect_" + v + ".js";
         if (user_link_target_prefix) {
           p = user_link_target_prefix + p;
         }
         demand_load(p, false);
       }
     }
  }
}

AddOnLoad(user_convert_all_links);
