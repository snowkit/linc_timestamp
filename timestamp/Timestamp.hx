package timestamp;

@:keep
@:include('linc_timestamp.h')
#if !display
@:build(linc.Linc.touch())
@:build(linc.Linc.xml('timestamp'))
#end
extern class Timestamp {

    @:native('linc::timestamp::now')
    static function now() : Float;

} //Timestamp