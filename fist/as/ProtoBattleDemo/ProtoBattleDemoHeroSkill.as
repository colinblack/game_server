package com.sanguo.game.server.connectlogic.common.message.ProtoBattleDemo
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleDemoHeroSkill
	{
		public static const PROTO:String = "ProtoBattleDemo.ProtoBattleDemoHeroSkill";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var type:int;
		public var s:Number;
		public var c:int;
		public var pc:int;
		public var pa:int;
		public function ProtoBattleDemoHeroSkill(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			id = undefined;
			type = undefined;
			s = undefined;
			c = undefined;
			pc = undefined;
			pa = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			if(this.type!= undefined)
			{
				serializeObj.type = this.type;
			}
			if(this.s!= undefined)
			{
				serializeObj.s = this.s;
			}
			if(this.c!= undefined)
			{
				serializeObj.c = this.c;
			}
			if(this.pc!= undefined)
			{
				serializeObj.pc = this.pc;
			}
			if(this.pa!= undefined)
			{
				serializeObj.pa = this.pa;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleDemoHeroSkill
		{
			id = undefined;
			type = undefined;
			s = undefined;
			c = undefined;
			pc = undefined;
			pa = undefined;
			this.id = msgObj.id;
			if(msgObj.hasOwnProperty("type"))
			{
				this.type = msgObj.type;
			}
			if(msgObj.hasOwnProperty("s"))
			{
				this.s = msgObj.s;
			}
			if(msgObj.hasOwnProperty("c"))
			{
				this.c = msgObj.c;
			}
			if(msgObj.hasOwnProperty("pc"))
			{
				this.pc = msgObj.pc;
			}
			if(msgObj.hasOwnProperty("pa"))
			{
				this.pa = msgObj.pa;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleDemoHeroSkill
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}