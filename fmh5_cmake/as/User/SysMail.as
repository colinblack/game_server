package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class SysMail
	{
		public static const PROTO:String = "User.SysMail";
		public var package_root:*;
		public  var message:*;
		public var ts:int;
		public var stat:int;
		public var sys:Byte;
		public var reward:Byte;
		public function SysMail(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			ts = undefined;
			stat = undefined;
			sys = undefined;
			reward = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.ts = this.ts;
			serializeObj.stat = this.stat;
			this.sys.pos = 0;
			this.reward.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SysMail
		{
			ts = undefined;
			stat = undefined;
			sys = undefined;
			reward = undefined;
			this.ts = msgObj.ts;
			this.stat = msgObj.stat;
			this.sys = new Byte();
			this.sys.writeArrayBuffer(msgObj.sys);
			this.sys.pos = 0;
			this.reward = new Byte();
			this.reward.writeArrayBuffer(msgObj.reward);
			this.reward.pos = 0;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):SysMail
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}