package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestKickOutBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestKickOutBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var memberUid:int;
		public function RequestKickOutBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			memberUid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			serializeObj.memberUid = this.memberUid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestKickOutBC
		{
			aid = undefined;
			uid = undefined;
			memberUid = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			this.memberUid = msgObj.memberUid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestKickOutBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}