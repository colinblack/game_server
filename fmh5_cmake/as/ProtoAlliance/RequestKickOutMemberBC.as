package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestKickOutMemberBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestKickOutMemberBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var memberUid:int;
		public function RequestKickOutMemberBC(root:*)
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
		public function unserialize(msgObj:*):RequestKickOutMemberBC
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
		public function decode(buffer:*):RequestKickOutMemberBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}