package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class RequestInviteJoinBC
	{
		public static const PROTO:String = "ProtoAlliance.RequestInviteJoinBC";
		public var package_root:*;
		public  var message:*;
		public var aid:int;
		public var uid:int;
		public var invitedUid:int;
		public var name:Byte;
		public function RequestInviteJoinBC(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			aid = undefined;
			uid = undefined;
			invitedUid = undefined;
			name = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.aid = this.aid;
			serializeObj.uid = this.uid;
			serializeObj.invitedUid = this.invitedUid;
			this.name.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):RequestInviteJoinBC
		{
			aid = undefined;
			uid = undefined;
			invitedUid = undefined;
			name = undefined;
			this.aid = msgObj.aid;
			this.uid = msgObj.uid;
			this.invitedUid = msgObj.invitedUid;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):RequestInviteJoinBC
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}