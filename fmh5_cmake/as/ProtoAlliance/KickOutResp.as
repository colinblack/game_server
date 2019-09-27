package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class KickOutResp
	{
		public static const PROTO:String = "ProtoAlliance.KickOutResp";
		public var package_root:*;
		public  var message:*;
		public var memberUid:int;
		public function KickOutResp(root:*)
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
		public function unserialize(msgObj:*):KickOutResp
		{
			memberUid = undefined;
			this.memberUid = msgObj.memberUid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):KickOutResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}