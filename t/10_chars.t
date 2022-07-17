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

my $examples1 = [
  [ '', ''],
  [ 'a', ''],
  [ '', 'b'],
  [ 'b', 'b'],
  ['ttatc__cg',
   '__agcaact'],
  ['abcabba_',
   'cb_ab_ac'],
   ['yqabc_',
    'zq__cb'],
  [ 'rrp',
    'rep'],
  [ 'a',
    'b' ],
  [ 'aa',
    'a_' ],
  [ 'abb',
    '_b_' ],
  [ 'a_',
    'aa' ],
  [ '_b_',
    'abb' ],
  [ 'ab',
    'cd' ],
  [ 'ab',
    '_b' ],
  [ 'ab_',
    '_bc' ],
  [ 'abcdef',
    '_bc___' ],
  [ 'abcdef',
    '_bcg__' ],
  [ 'xabcdef',
    'y_bc___' ],
  [ 'öabcdef',
    'ü§bc___' ],
  [ 'o__horens',
    'ontho__no'],
  [ 'Jo__horensis',
    'Jontho__nota'],
  [ 'horen',
    'ho__n'],
  [ 'Chrerrplzon',
    'Choereph_on'],
  [ 'Chrerr',
    'Choere'],
  [ 'rr',
    're'],
  [ 'abcdefg_',
    '_bcdefgh'],

  [ 'aabbcc',
    'abc'],
  [ 'aaaabbbbcccc',
    'abc'],
  [ 'aaaabbcc',
    'abc'],
  [ 'ſhoereſhoſ',
    'Choerephon'],
];



my $examples2 = [
  [ 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVY_', # l=52
    '_bcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVYZ'],
  [ 'abcdefghijklmnopqrstuvwxyz0123456789!"$%&/()=?ABCDEFGHIJKLMNOPQRSTUVY_',
    '_bcdefghijklmnopqrstuvwxyz0123456789!"$%&/()=?ABCDEFGHIJKLMNOPQRSTUVYZ'],
  [ 'abcdefghijklmnopqrstuvwxyz0123456789"$%&/()=?ABCDEFGHIJKLMNOPQRSTUVY_',
    '!'],
  [ '!',
    'abcdefghijklmnopqrstuvwxyz0123456789"$%&/()=?ABCDEFGHIJKLMNOPQRSTUVY_'],
  [ 'abcdefghijklmnopqrstuvwxyz012345678!9!"$%&/()=?ABCDEFGHIJKLMNOPQRSTUVYZ',
    'abcdefghijklmnopqrstuvwxyz012345678_9!"$%&/()=?ABCDEFGHIJKLMNOPQRSTUVYZ'],
  [ 'abcdefghijklmnopqrstuvwxyz012345678_9!"$%&/()=?ABCDEFGHIJKLMNOPQRSTUVYZ',
    'abcdefghijklmnopqrstuvwxyz012345678!9!"$%&/()=?ABCDEFGHIJKLMNOPQRSTUVYZ'],
  [ 'aaabcdefghijklmnopqrstuvwxyz012345678_9!"$%&/()=?ABCDEFGHIJKLMNOPQRSTUVYZZZ',
    'a!Z'],
];

# prefix/suffix optimisation
my $examples3 = [
  [ 'a',
    'a', ],
  [ 'aa',
    'aa', ],
  [ 'a_',
    'aa', ],
  [ 'aa',
    'a_', ],
  [ '_b_',
    'abb', ],
  [ 'abb',
    '_b_', ],
];


if (1) {
    for my $example (@$examples1) {
        my $a = $example->[0];

        my $length = length($a);

        is(
            &Wollmers::Utf8::XS::jb_chars($a),
            $length,
            "jb_chars [$a] -> " . $length
        );
        is(
            &Wollmers::Utf8::XS::cp_chars($a),
            $length,
            "cp_chars [$a] -> " . $length
        );
        is(
            &Wollmers::Utf8::XS::sc_chars($a),
            $length,
            "sc_chars [$a] -> " . $length
        );
    }
}

if (1) {
    for my $example (@$examples2) {
        my $a = $example->[0];

        my $length = length($a);

        is(
            &Wollmers::Utf8::XS::jb_chars($a),
            $length,
            "jb_chars [$a] -> " . $length
        );
        is(
            &Wollmers::Utf8::XS::cp_chars($a),
            $length,
            "cp_chars [$a] -> " . $length
        );
        is(
            &Wollmers::Utf8::XS::sc_chars($a),
            $length,
            "sc_chars [$a] -> " . $length
        );
    }
}


if (1) {
    for my $example (@$examples3) {
        my $a = $example->[0];

        my $length = length($a);

        is(
            &Wollmers::Utf8::XS::jb_chars($a),
            $length,
            "jb_chars [$a] -> " . $length
        );
        is(
            &Wollmers::Utf8::XS::cp_chars($a),
            $length,
            "cp_chars [$a] -> " . $length
        );
        is(
            &Wollmers::Utf8::XS::sc_chars($a),
            $length,
            "sc_chars [$a] -> " . $length
        );
    }
}


# test error-by-one
if (1) {
  my @strings = ('a', 'ſ', 'य', "\x{10980}");
  for my $string1 (@strings) {
    # $ uni identify ſ
    #      cpoint  dec    utf-8       html       name
    # 'ſ'  U+017F  383    c5 bf       &#x17f;    LATIN SMALL LETTER LONG S (Lowercase_Letter)
    #my $string1 = 'ſ'; # long s

    # $ uni identify य
    #      cpoint  dec    utf-8       html       name
    # 'य'  U+092F  2351   e0 a4 af    &#x92f;    DEVANAGARI LETTER YA (Other_Letter)
    # my $string1 = 'य'; # Hindi
    #my $string1 = "\x{092F}"; # 'य'

    # $ uni print U+10980
    #       cpoint  dec    utf-8       html       name
    # '𐦀'  U+10980 67968  f0 90 a6 80 &#x10980;  MEROITIC HIEROGLYPHIC LETTER A (Other_Letter)
    #my $string1 = "\x{10980}"; # '𐦀'

    my @base_lengths = (1, 2, 4, 8, 16, 32, 64, 128, 256);
    #my @base_lengths = (2,);

    for my $base_length (@base_lengths) {
        for my $delta (-1, 0, 1) {
            my $mult = $base_length + $delta;
            my $a = $string1 x $mult;

            my $length = length($a);

            is(
                &Wollmers::Utf8::XS::jb_chars($a),
                $length,
                "jb_chars [$string1 x $mult] -> " . $length
            );
            is(
                &Wollmers::Utf8::XS::cp_chars($a),
                $length,
                "cp_chars [$string1 x $mult] -> " . $length
                );
            is(
                &Wollmers::Utf8::XS::sc_chars($a),
                $length,
                "sc_chars [$string1 x $mult] -> " . $length
            );

        }
    }
  }
}

=pod
# HINDI for testing combining characters
if (1) {
    my $string1 = 'राज्य';
    my $string2 = 'उसकी';
    my @base_lengths = (16);

    for my $base_length1 (@base_lengths) {
        my $mult1 = int($base_length1/length($string1)) + 1;
        my @a = split(//,$string1 x $mult1);
        my $m = scalar @a;
        for my $base_length2 (@base_lengths) {
            my $mult2 = int($base_length2/length($string2)) + 1;
            my @b = split(//,$string2 x $mult2);
            my $n = scalar @b;

            my $A = join('',@a);
            my $B = join('',@b);

            is(
                &Text::Levenshtein::BVXS::distance($A,$B),
                distance($A, $B),
                "[$string1 x $mult1] m: $m, [$string2 x $mult2] n: $n -> "
                    . distance($A, $B)
            );
        }
    }
}

# MEROITIC HIEROGLYPHIC LETTERs
if (1) {
    my $string1 = "\x{10980}\x{10981}\x{10983}";
    my $string2 = "\x{10981}\x{10980}\x{10983}\x{10982}";
    my @base_lengths = (16);

    for my $base_length1 (@base_lengths) {
        my $mult1 = int($base_length1/length($string1)) + 1;
        my @a = split(//,$string1 x $mult1);
        my $m = scalar @a;
        for my $base_length2 (@base_lengths) {
            my $mult2 = int($base_length2/length($string2)) + 1;
            my @b = split(//,$string2 x $mult2);
            my $n = scalar @b;

            my $A = join('',@a);
            my $B = join('',@b);

            is(
                &Text::Levenshtein::BVXS::distance($A,$B),
                distance($A, $B),
                "[$string1 x $mult1] m: $m, [$string2 x $mult2] n: $n -> "
                    . distance($A, $B)
            );
        }
    }
}

my @data3 = ([qw/a b d/ x 50], [qw/b a d c/ x 50]);

if (0) {
  is(
    Text::Levenshtein::BV->distance(@data3),
    distance(@data3),

    '[qw/a b d/ x 50], [qw/b a d c/ x 50] -> ' . distance(@data3)
  );

}

=cut

done_testing;
