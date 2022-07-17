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

ok(1);

my $string;
my $v;

$string = 'Abcdefg'; # 7 Characters = 7 byte
print "\n",'$string: ',$string,' chars: 7 bytes:: 7',"\n";
if (1) {
    cmpthese( -1, {
        'length' => sub {
            $v = length($string);
        },
        'jb_chars' => sub {
            $v = &Wollmers::Utf8::XS::jb_chars($string);
        },
        'cp_chars' => sub {
            $v = &Wollmers::Utf8::XS::cp_chars($string);
        },
        'sc_chars' => sub {
            $v = &Wollmers::Utf8::XS::sc_chars($string);
        },
    });
}

$string = 'Abcdefgh'; # 8 Characters = 8 byte
print "\n",'$string: ',$string,' chars: 8 bytes: 8',"\n";
if (1) {
    cmpthese( -1, {
        'length' => sub {
            $v = length($string);
        },
        'jb_chars' => sub {
            $v = &Wollmers::Utf8::XS::jb_chars($string);
        },
        'cp_chars' => sub {
            $v = &Wollmers::Utf8::XS::cp_chars($string);
        },
        'sc_chars' => sub {
            $v = &Wollmers::Utf8::XS::sc_chars($string);
        },
    });
}

$string = 'Chſerſplzon'; # 11 Characters = 13 byte

if (0) {
        my $length = length($string);

        is(
            &Wollmers::Utf8::XS::jb_chars($string),
            $length,
            "jb_chars [$string] -> " . $length
        );
        is(
            &Wollmers::Utf8::XS::cp_chars($string),
            $length,
            "cp_chars [$string] -> " . $length
        );
        is(
            &Wollmers::Utf8::XS::sc_chars($string),
            $length,
            "sc_chars [$string] -> " . $length
        );
}

print "\n",'$string: ',$string,' chars: 11 bytes: 13',"\n";
if (1) {
    cmpthese( -1, {
        'length' => sub {
            $v = length($string);
        },
        'jb_chars' => sub {
            $v = &Wollmers::Utf8::XS::jb_chars($string);
        },
        'cp_chars' => sub {
            $v = &Wollmers::Utf8::XS::cp_chars($string);
        },
        'sc_chars' => sub {
            $v = &Wollmers::Utf8::XS::sc_chars($string);
        },
    });
}

$string = 'राज्यराज्य'; # 9 characters = 27 byte

print "\n",'$string: ',$string,' chars: 9 bytes: 27',"\n";

if (1) {
    cmpthese( -1, {
        'length' => sub {
            $v = length($string);
        },
        'jb_chars' => sub {
            $v = &Wollmers::Utf8::XS::jb_chars($string);
        },
        'cp_chars' => sub {
            $v = &Wollmers::Utf8::XS::cp_chars($string);
        },
        'sc_chars' => sub {
            $v = &Wollmers::Utf8::XS::sc_chars($string);
        },
    });
}

$string = 'Chſerſplzon' x 8; # 11*8=88 Characters = 13*8=104 byte

print "\n",'$string: ','Chſerſplzon x 8',' chars: 88 bytes: 104',"\n";

if (1) {
    cmpthese( -1, {
        'length' => sub {
            $v = length($string);
        },
        'jb_chars' => sub {
            $v = &Wollmers::Utf8::XS::jb_chars($string);
        },
        'cp_chars' => sub {
            $v = &Wollmers::Utf8::XS::cp_chars($string);
        },
        'sc_chars' => sub {
            $v = &Wollmers::Utf8::XS::sc_chars($string);
        },
    });
}

done_testing;
