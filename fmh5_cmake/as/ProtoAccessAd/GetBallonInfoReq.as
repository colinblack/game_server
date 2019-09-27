package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class GetBallonInfoReq
	{
		public static const PROTO:String = "ProtoAccessAd.GetBallonInfoReq";
		public var package_root:*;
		public  var message:*;
		public function GetBallonInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetBallonInfoReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetBallonInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}