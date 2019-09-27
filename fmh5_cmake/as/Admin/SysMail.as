package com.sanguo.game.server.connectlogic.common.message.Admin
{
	import laya.utils.Byte;
	public class SysMail
	{
		public static const PROTO:String = "Admin.SysMail";
		public var package_root:*;
		public  var message:*;
		public var uid:Vector.<int>;
		public var sys:Byte;
		public var reward:Byte;
		public function SysMail(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			uid = new Vector.<int>();
			sys = undefined;
			reward = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.uid = [];
			for(var i:int = 0;i < this.uid.length;i++)
			{
				serializeObj.uid.push(this.uid[i]);
			}
			this.sys.pos = 0;
			this.reward.pos = 0;
			return serializeObj;
		}
		public function unserialize(msgObj:*):SysMail
		{
			uid = new Vector.<int>();
			sys = undefined;
			reward = undefined;
			for(var i:int = 0;i < msgObj.uid.length;i++)
			{
				this.uid.push(msgObj.uid[i]);
			}
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