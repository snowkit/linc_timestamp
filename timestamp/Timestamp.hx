package timestamp;

@:keep
@:include('linc_timestamp.h')
@:build(linc.Linc.touch())
@:build(linc.Linc.xml('timestamp'))
extern class Timestamp {

    @:native('linc::timestamp::now')
    static function now() : Float;

} //Timestamp