#include <string>
#include <set>
#include <vector>
#include <tlgsutils/url_parser.hpp>

bool inBlacklist(const std::string& url_str)
{
    tlgs::Url url(url_str);
    // TODO: Make this live on SQL
    static const std::set<std::string> blacklist_domains = {
        // example sites
        "example.com",
        "example.org",
        "example.net",
        "example.io",
        "example.us",
        "example.eu",
        "example.gov",
        "example.space",
        "gus.guru", // GUS no longer exists
        "ftrv.se", // Blocked me when developing the search engine. Waisting my time on timeout
        "gmi.bacardi55.io", // No longer exists
    };

    static const std::vector<std::string> blacklist_urls = {
        // Mostly imported from geminispace.info.


        "gemini://www.youtube.com/",

        // all combinations of a tictactoe board
        "gemini://tictactoe.lanterne.chilliet.eu",

        // serving big files and slooow capsule -> takes to long to crawl
        "gemini://kamalatta.ddnss.de/",
        "gemini://tweek.zyxxyz.eu/valentina/",

        // ASCII art with emulated modem speed
        "gemini://ansi.hrtk.in/",
        "gemini://matrix.kiwifarms.net",

        // ZachDeCooks songs
        "gemini://songs.zachdecook.com/song.gmi.php/",
        "gemini://songs.zachdecook.com/chord.svg/",
        "gemini://gemini.zachdecook.com/cgi-bin/ccel.sh",

        // kwiecien gemcast
        "gemini://kwiecien.us/gemcast/",

        // breaks crawl due to recursion overflow
        "gemini://cadence.moe/chapo/",

        "gemini://nixo.xyz/reply/", 
        "gemini://nixo.xyz/notify",
        "gemini://gemini.thebackupbox.net/queryresponse",
        "gemini://gem.garichankar.com/share_audio", 

        // Mastodon mirror
        "gemini://vps01.rdelaage.ovh/",
        "gemini://mastogem.picasoft.net",

        // various failing resources on runjimmyrunrunyoufuckerrun.com
        "gemini://runjimmyrunrunyoufuckerrun.com/fonts/",
        "gemini://runjimmyrunrunyoufuckerrun.com/tmp/",

        // Search providers 
        "gemini://houston.coder.town/search?",
        "gemini://houston.coder.town/search/",
        "gemini://marginalia.nu/search",

        // Geddit
        "gemini://geddit.pitr.ca/post?",
        "gemini://geddit.pitr.ca/c/",
        "gemini://geddit.glv.one/post?",
        "gemini://geddit.glv.one/c/",
        
        // Marmaladefoo calculator
        "gemini://gemini.marmaladefoo.com/cgi-bin/calc.cgi?",
        "gemini://gemini.circumlunar.space/users/fgaz/calculator/",

        // Individual weather pages
        "gemini://acidic.website/cgi-bin/weather.tcl?",
        "gemini://caolan.uk/weather/",

        // Alex Schroeder's problematic stuff
        "gemini://alexschroeder.ch/image_external",
        "gemini://alexschroeder.ch/html/",
        "gemini://alexschroeder.ch/diff/",
        "gemini://alexschroeder.ch/history/",
        "gemini://alexschroeder.ch/http",
        "gemini://alexschroeder.ch/https",
        "gemini://alexschroeder.ch/tag/",
        "gemini://alexschroeder.ch/raw/",
        "gemini://alexschroeder.ch/map/",
        "gemini://alexschroeder.ch/do/comment",
        "gemini://alexschroeder.ch/do/rc",
        "gemini://alexschroeder.ch/do/rss",
        "gemini://alexschroeder.ch/do/new",
        "gemini://alexschroeder.ch/do/more",
        "gemini://alexschroeder.ch/do/tags",
        "gemini://alexschroeder.ch/do/match",
        "gemini://alexschroeder.ch/do/search",
        "gemini://alexschroeder.ch/do/gallery/",

        // mozz mailing list linkscraper 
        "gemini://mozz.us/files/gemini-links.gmi",
        "gemini://gem.benscraft.info/mailing-list",
        " gemini://rawtext.club/~sloum/geminilist",
        // gemini.techrights.org
        "gemini://gemini.techrights.org/",

        // youtube mirror
        "gemini://pon.ix.tc/cgi-bin/youtube.cgi?",
        "gemini://pon.ix.tc/youtube/",
        
        // news mirrors - not our business
        // TLGS can handle some news. Let's keep them for now
        // "gemini://guardian.shit.cx/", // NOTE: at least try to index one new site!
        "gemini://simplynews.metalune.xyz",
        "gemini://illegaldrugs.net/cgi-bin/news.php?",
        "gemini://illegaldrugs.net/cgi-bin/reader",
        "gemini://rawtext.club/~sloum/geminews",
        "gemini://gemini.cabestan.tk/hn",
        "gemini://hn.filiuspatris.net/",
        "gemini://schmittstefan.de/de/nachrichten/",
        "gemini://gmi.noulin.net/mobile",
        "gemini://jpfox.fr/rss/",
        "gemini://illegaldrugs.net/cgi-bin/news.php/",
        "gemini://dw.schettler.net/",
        "gemini://dioskouroi.xyz/top",
        "gemini://drewdevault.com/cgi-bin/hn.py",
        "gemini://tobykurien.com/maverick/",
        
        // wikipedia proxy
        "gemini://wp.pitr.ca/",
        "gemini://wp.glv.one/",
        "gemini://wikipedia.geminet.org/",
        "gemini://wikipedia.geminet.org:1966",
        "gemini://vault.transjovian.org/",
        
        // client torture test
        "gemini://egsam.pitr.ca/",
        "gemini://egsam.glv.one/",
        "gemini://gemini.conman.org/test",

        // mozz's chat
        "gemini://chat.mozz.us/stream",
        "gemini://chat.mozz.us/submit",

        // gopher proxy
        "gemini://80h.dev/agena/",

        // astrobotany
        "gemini://astrobotany.mozz.us/",
        "gemini://carboncopy.xyz/cgi-bin/apache.gex/",

        // susa.net
        "gemini://gemini.susa.net/cgi-bin/search?",
        "gemini://gemini.susa.net/cgi-bin/twitter?",
        "gemini://gemini.susa.net/cgi-bin/vim-search?",
        "gemini://gemini.susa.net/cgi-bin/links_stu.lua?",

        "gemini://gemini.spam.works/textfiles/",
        "gemini://gemini.spam.works/mirrors/textfiles/",
        "gemini://gemini.spam.works/users/dvn/archive/",

        // streams that never end...
        "gemini://gemini.thebackupbox.net/radio",
        "gemini://higeki.jp/radio",

        //  full web proxy
        "gemini://drewdevault.com/cgi-bin/web.sh?",
        "gemini://gemiprox.pollux.casa/",
        "gemini://gemiprox.pollux.casa:1966",
        "gemini://ecs.d2evs.net/proxy/",
        "gemini://gmi.si3t.ch/www-gem/",
        "gemini://orrg.clttr.info/orrg.pl",

        // killing crawl, I think maybe because it's too big
        // cryptocurrency bullshit
        "gemini://gem.denarii.cloud/",

        // docs - not our business
        "gemini://cfdocs.wetterberg.nu/",
        "gemini://godocs.io",
        "gemini://emacswiki.org/page/",

        // He doen't like bots. As your wish (Just put up a robots.txt)
        "gemini://alexschroeder.ch/",

        // Too much code
        "gemini://si3t.ch/code/",
        "gemini://tilde.club/~filip/library/",
        "gemini://gemini.bortzmeyer.org/rfc-mirror/",
        "gemini://chris.vittal.dev/rfcs",
        "gemini://going-flying.com/git/cgi/gemini.git/",
        "gemini://szczezuja.flounder.online/git/"
    };

    if(blacklist_domains.count(url.host()) != 0)
        return true;
    for(const auto& blocked : blacklist_urls) {
        if(url.str().find(blocked) == 0)
            return true;
    }

    // No to all antenna API endpoints
    if(url.path().find("~antenna/filter/") != std::string::npos)
        return false;
    return false;
}