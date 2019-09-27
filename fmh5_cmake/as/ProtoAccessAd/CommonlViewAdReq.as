package com.sanguo.game.server.connectlogic.common.message.ProtoAccessAd
{
	import laya.utils.Byte;
	public class CommonlViewAdReq
	{
		public static const PROTO:String = "ProtoAccessAd.CommonlViewAdReq";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public function CommonlViewAdReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = this.type;
			return serializeObj;
		}
		public function unserialize(msgObj:*):CommonlViewAdReq
		{
			type = undefined;
			this.type = msgObj.type;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):CommonlViewAdReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}