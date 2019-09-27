package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AllianceNotifyCPP
	{
		public static const PROTO:String = "ProtoAlliance.AllianceNotifyCPP";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var announcer:int;
		public var name:Byte;
		public var content:Byte;
		public var createts:int;
		public function AllianceNotifyCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			announcer = undefined;
			name = undefined;
			content = undefined;
			createts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.announcer = this.announcer;
			this.name.pos = 0;
			this.content.pos = 0;
			serializeObj.createts = this.createts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AllianceNotifyCPP
		{
			id = undefined;
			announcer = undefined;
			name = undefined;
			content = undefined;
			createts = undefined;
			this.id = msgObj.id;
			this.announcer = msgObj.announcer;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			this.content = new Byte();
			this.content.writeArrayBuffer(msgObj.content);
			this.content.pos = 0;
			this.createts = msgObj.createts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AllianceNotifyCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}