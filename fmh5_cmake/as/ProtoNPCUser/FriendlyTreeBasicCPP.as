package com.sanguo.game.server.connectlogic.common.message.ProtoNPCUser
{
	import laya.utils.Byte;
	public class FriendlyTreeBasicCPP
	{
		public static const PROTO:String = "ProtoNPCUser.FriendlyTreeBasicCPP";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var othuid:int;
		public var name:Byte;
		public var head:Byte;
		public var ts:int;
		public function FriendlyTreeBasicCPP(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			othuid = undefined;
			name = undefined;
			head = undefined;
			ts = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.othuid = this.othuid;
			this.name.pos = 0;
			this.head.pos = 0;
			serializeObj.ts = this.ts;
			return serializeObj;
		}
		public function unserialize(msgObj:*):FriendlyTreeBasicCPP
		{
			id = undefined;
			othuid = undefined;
			name = undefined;
			head = undefined;
			ts = undefined;
			this.id = msgObj.id;
			this.othuid = msgObj.othuid;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			this.head = new Byte();
			this.head.writeArrayBuffer(msgObj.head);
			this.head.pos = 0;
			this.ts = msgObj.ts;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FriendlyTreeBasicCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}