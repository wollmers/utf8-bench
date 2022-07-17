#!perl
use 5.008;

use strict;
use warnings;
use utf8;

binmode(STDOUT,":encoding(UTF-8)");
binmode(STDERR,":encoding(UTF-8)");

#use lib qw(../blib/);

use Test::More;
use Test::More::UTF8;

use Wollmers::Utf8::XS;

use Benchmark qw(:all);
#use Encode        qw[];
#use Unicode::UTF8 qw[];

#my $enc = Encode::find_encoding('UTF-8')
#  || die(q/find_encoding('UTF-8')/);

my $octets;

$octets = 'Abcdefg'; # 7 Characters = 7 byte
print "\n",'$octets: ',$octets,' chars: 7 bytes 7',"\n";
if (1) {
    cmpthese( -1, {
        'jb_chars' => sub {
            my $v = &Wollmers::Utf8::XS::jb_chars($octets);
        },
        'cp_chars' => sub {
            my $v = &Wollmers::Utf8::XS::cp_chars($octets);
        },
        'sc_chars' => sub {
            my $v = &Wollmers::Utf8::XS::sc_chars($octets);
        },
    });
}

$octets = 'Abcdefgh'; # 8 Characters = 8 byte
print "\n",'$octets: ',$octets,' chars: 8 bytes 8',"\n";
if (1) {
    cmpthese( -1, {
        'jb_chars' => sub {
            my $v = &Wollmers::Utf8::XS::jb_chars($octets);
        },
        'cp_chars' => sub {
            my $v = &Wollmers::Utf8::XS::cp_chars($octets);
        },
        'sc_chars' => sub {
            my $v = &Wollmers::Utf8::XS::sc_chars($octets);
        },
    });
}

$octets = 'Chſerſplzon'; # 11 Characters = 13 byte
        my $length = length($octets);

        is(
            &Wollmers::Utf8::XS::jb_chars($octets),
            $length,
            "jb_chars [$octets] -> " . $length
        );
        is(
            &Wollmers::Utf8::XS::cp_chars($octets),
            $length,
            "cp_chars [$octets] -> " . $length
        );
        is(
            &Wollmers::Utf8::XS::sc_chars($octets),
            $length,
            "sc_chars [$octets] -> " . $length
        );

print "\n",'$octets: ',$octets,' chars: 11 bytes 13',"\n";
if (1) {
    cmpthese( -1, {
        'jb_chars' => sub {
            my $v = &Wollmers::Utf8::XS::jb_chars($octets);
        },
        'cp_chars' => sub {
            my $v = &Wollmers::Utf8::XS::cp_chars($octets);
        },
        'sc_chars' => sub {
            my $v = &Wollmers::Utf8::XS::sc_chars($octets);
        },
    });
}

$octets = 'राज्यराज्य'; # 9 characters = 27 byte

print "\n",'$octets: ',$octets,' chars: 9 bytes 27',"\n";

if (1) {
    cmpthese( -1, {
        'jb_chars' => sub {
            my $v = &Wollmers::Utf8::XS::jb_chars($octets);
        },
        'cp_chars' => sub {
            my $v = &Wollmers::Utf8::XS::cp_chars($octets);
        },
        'sc_chars' => sub {
            my $v = &Wollmers::Utf8::XS::sc_chars($octets);
        },
    });
}

done_testing;
