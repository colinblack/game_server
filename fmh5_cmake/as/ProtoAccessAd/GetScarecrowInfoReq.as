package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class GetScarecrowInfoReq
	{
		public static const PROTO:String = "ProtoAccessAd.GetScarecrowInfoReq";
		public var package_root:*;
		public  var message:*;
		public function GetScarecrowInfoReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetScarecrowInfoReq
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetScarecrowInfoReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}