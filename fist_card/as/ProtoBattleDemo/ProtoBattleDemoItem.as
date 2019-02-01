package com.sanguo.game.server.connectlogic.common.message.ProtoBattleDemo
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleDemoItem
	{
		public static const PROTO:String = "ProtoBattleDemo.ProtoBattleDemoItem";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var type:int;
		public var s:Number;
		public var c:int;
		public var turn:int;
		public function ProtoBattleDemoItem(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			id = undefined;
			type = undefined;
			s = undefined;
			c = undefined;
			turn = undefined;
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
			if(this.turn!= undefined)
			{
				serializeObj.turn = this.turn;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleDemoItem
		{
			id = undefined;
			type = undefined;
			s = undefined;
			c = undefined;
			turn = undefined;
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
			if(msgObj.hasOwnProperty("turn"))
			{
				this.turn = msgObj.turn;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleDemoItem
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}