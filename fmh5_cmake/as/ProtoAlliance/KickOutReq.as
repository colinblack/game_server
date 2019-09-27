package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class KickOutReq
	{
		public static const PROTO:String = "ProtoAlliance.KickOutReq";
		public var package_root:*;
		public  var message:*;
		public var memberUid:int;
		public function KickOutReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			memberUid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.memberUid = this.memberUid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):KickOutReq
		{
			memberUid = undefined;
			this.memberUid = msgObj.memberUid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):KickOutReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}