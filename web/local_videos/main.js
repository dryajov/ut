var baseUrl = "http://ktechpit.com/USS/Olivia/"

$(document).bind("mobileinit", function(){
        $.mobile.defaultPageTransition = 'slidefade';
        $.mobile.ajaxEnabled = true;
        $.mobile.hideUrlBar = false;
});

//persist navbar
$(function() {
    $( "[data-role='navbar']" ).navbar();
    $( "[data-role='header']" ).toolbar();
 });




// Update the contents of the toolbars
$( document ).on( "pageshow", "[data-role='page']", function() {
    // Each of the four pages in this demo has a data-title attribute
    // which value is equal to the text of the nav button
    // For example, on first page: <div data-role="page" data-title="Info">
    var current = $( this ).jqmData( "title" );
    // Change the heading
    $( "[data-role='header'] h1" ).text( current );
    // Remove active class from nav buttons
    $( "[data-role='navbar'] a.ui-btn-active" ).removeClass( "ui-btn-active" );
    // Add active class to current nav button
    $( "[data-role='navbar'] a" ).each(function() {
        if ( $( this ).text() === current ) {
            $( this ).addClass( "ui-btn-active" );
        }
    });
});


function showLoading() {
     $.mobile.loading("show", {
        text: "Loading..",
        textVisible: false,
        theme: "b",
        overlay: true
    });
}




var title,artist,album,coverUrl,songId,albumId,artistId,millis;
var base64; //returns base64 versio of album art to c++
var colorThief ; // colorThief object init
var dominantColor; //global
var html_data; //global html_data for youtube search
var album_loaded = false;
var track_loaded = false;
var artist_loaded = false;


$(document).ready(function($) {

    $(function () {
        $("[data-role=popup]").popup().enhanceWithin();
    });

    $(function() {
           $.mobile.defaultHomeScroll = 0;
    });

    $("#coverImage").load(function(){
          dominantColor = colorThief.getColor(document.querySelector("#coverImage"));
    });
});


//  core functions -------------
function open_local_saved_videos(){
    $("#saved_tracks_result").empty();
    showLoading();
    $.mobile.changePage($('#tracks_page'));
    var json = JSON.parse(store.web_print_local_saved_videos()); //songs Data is returned in json format
    var $html = "";
    $( ".ui-page-active [data-role='header'] h1" ).html(json.length+" downloaded videos");
    for(var i= 0; i < json.length;i++){
        var albumType = (json[i].album === "undefined") ? "Youtube":"";
         $html = $html+
            "<li onclick='mainwindow.playVideo(\""+json[i].songId+"\")' data-filtertext='"+json[i].title+" "+json[i].album+" "+json[i].artist+"' ><a>"+
            "<img id='"+json[i].songId+"' style='max-width:100px;max-height:144px;width=100px;height=100px;' id='' src='data:image/png;base64,"+json[i].base64+"' \>"+
                    "<p>"+
                        ""+json[i].title+
                        "<br>"+
                        "Album: "+json[i].album+
                        "<br>"+
                        "Artist: "+json[i].artist+
                    "</p>"+
                  "<p class='ui-li-aside'>"+albumType+"</p>" +
               " </a>"+
            "</li>";
    }
    $.mobile.loading("hide");
    $("#saved_tracks_result").append($html).listview("refresh");
    $('#tracks_page .ui-content').trigger('create');
    $('#tracks_page .ui-content').fadeIn('slow');
}

$(document).on("pagecreate", "#tracks_page", function(){
    $('#a-search, #closeSearch').on('vclick', function (event) {
        $('#songsfilter-input-form').toggleClass('moved');
    });
});

function toDataUrl(url, callback) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function() {
        var reader = new FileReader();
        reader.onloadend = function() {
            callback(reader.result);
        }
        reader.readAsDataURL(xhr.response);
    };
    xhr.open('GET', url);
    xhr.responseType = 'blob';
    xhr.send();
}



function gettrackinfo(searchterm){
    colorThief = new ColorThief();
    var arr = searchterm.split("!=-=!")
    title = arr[0];
    artist = arr[1];
    album = arr[2];
    coverUrl = arr[3];
    songId = arr[4];
    albumId = arr[5];
    artistId= arr[6];
    millis = arr[7];

    var query = title.replace("N/A","")+" - "+artist.replace("N/A","")+" - "+album.replace("N/A","");

    console.log(query);

    showLoading();

    toDataUrl(coverUrl, function(myBase64) {
        base64 = myBase64;
        document.querySelector("#coverImage").setAttribute("src",coverUrl);
        $.ajax({
            url: baseUrl+"youtube.php",
                   type:"GET",
                   data:{
                        "query": query,
                        "millis": millis
                   },
            success: function(html) {
                html_data =html;
                mainwindow.addToQueue(html_data,title,artist,album,base64,dominantColor,songId,albumId,artistId);
                $.mobile.loading("hide");
            }
        });

    });
}




