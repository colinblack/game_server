package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class GetLastViewAdTsReq
	{
		public static const PROTO:String = "ProtoAccessAd.GetLastViewAdTsReq";
		public var package_root:*;
		public  var message:*;
		public function GetLastViewAdTsReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetLastViewAdTsReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetLastViewAdTsReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}