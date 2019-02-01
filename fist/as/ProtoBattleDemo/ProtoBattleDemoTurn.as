package com.sanguo.game.server.connectlogic.common.message.ProtoBattleDemo
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleDemoTurn
	{
		public static const PROTO:String = "ProtoBattleDemo.ProtoBattleDemoTurn";
		public var package_root:*;
		public  var message:*;
		public var skillindex:int;
		public var itemindex:int;
		public var skilldam:int;
		public var crit:Boolean;
		public var extradam:int;
		public function ProtoBattleDemoTurn(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			skillindex = undefined;
			itemindex = undefined;
			skilldam = undefined;
			crit = undefined;
			extradam = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.skillindex = this.skillindex;
			serializeObj.itemindex = this.itemindex;
			if(this.skilldam!= undefined)
			{
				serializeObj.skilldam = this.skilldam;
			}
			if(this.crit!= undefined)
			{
				serializeObj.crit = this.crit;
			}
			if(this.extradam!= undefined)
			{
				serializeObj.extradam = this.extradam;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleDemoTurn
		{
			skillindex = undefined;
			itemindex = undefined;
			skilldam = undefined;
			crit = undefined;
			extradam = undefined;
			this.skillindex = msgObj.skillindex;
			this.itemindex = msgObj.itemindex;
			if(msgObj.hasOwnProperty("skilldam"))
			{
				this.skilldam = msgObj.skilldam;
			}
			if(msgObj.hasOwnProperty("crit"))
			{
				this.crit = msgObj.crit;
			}
			if(msgObj.hasOwnProperty("extradam"))
			{
				this.extradam = msgObj.extradam;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleDemoTurn
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}