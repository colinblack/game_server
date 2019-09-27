package com.sanguo.game.server.connectlogic.common.message.ProtoAlliance
{
	import laya.utils.Byte;
	public class AllianceRaceMemberOrder
	{
		public static const PROTO:String = "ProtoAlliance.AllianceRaceMemberOrder";
		public var package_root:*;
		public  var message:*;
		public var uid:int;
		public var id:int;
		public var ts:int;
		public var level:int;
		public var name:Byte;
		public var fig:Byte;
		public function AllianceRaceMemberOrder(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = undefined;
			id = undefined;
			ts = undefined;
			level = undefined;
			name = undefined;
			fig = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = this.uid;
			serializeObj.id = this.id;
			serializeObj.ts = this.ts;
			serializeObj.level = this.level;
			this.name.pos = 0;
			this.fig.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):AllianceRaceMemberOrder
		{
			uid = undefined;
			id = undefined;
			ts = undefined;
			level = undefined;
			name = undefined;
			fig = undefined;
			this.uid = msgObj.uid;
			this.id = msgObj.id;
			this.ts = msgObj.ts;
			this.level = msgObj.level;
			this.name = new Byte();
			this.name.writeArrayBuffer(msgObj.name);
			this.name.pos = 0;
			this.fig = new Byte();
			this.fig.writeArrayBuffer(msgObj.fig);
			this.fig.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):AllianceRaceMemberOrder
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}