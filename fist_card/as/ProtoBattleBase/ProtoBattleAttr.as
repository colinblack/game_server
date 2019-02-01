package com.sanguo.game.server.connectlogic.common.message.ProtoBattleBase
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleAttr
	{
		public static const PROTO:String = "ProtoBattleBase.ProtoBattleAttr";
		public var package_root:*;
		public  var message:*;
		public var heroid:int;
		public var hp:int;
		public var att:int;
		public var def:int;
		public var shield:int;
		public var battlePower:int;
		public var damInc:Number;
		public var damDec:Number;
		public function ProtoBattleAttr(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			heroid = undefined;
			hp = undefined;
			att = undefined;
			def = undefined;
			shield = undefined;
			battlePower = undefined;
			damInc = undefined;
			damDec = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.heroid = this.heroid;
			if(this.hp!= undefined)
			{
				serializeObj.hp = this.hp;
			}
			if(this.att!= undefined)
			{
				serializeObj.att = this.att;
			}
			if(this.def!= undefined)
			{
				serializeObj.def = this.def;
			}
			if(this.shield!= undefined)
			{
				serializeObj.shield = this.shield;
			}
			if(this.battlePower!= undefined)
			{
				serializeObj.battlePower = this.battlePower;
			}
			if(this.damInc!= undefined)
			{
				serializeObj.damInc = this.damInc;
			}
			if(this.damDec!= undefined)
			{
				serializeObj.damDec = this.damDec;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleAttr
		{
			heroid = undefined;
			hp = undefined;
			att = undefined;
			def = undefined;
			shield = undefined;
			battlePower = undefined;
			damInc = undefined;
			damDec = undefined;
			this.heroid = msgObj.heroid;
			if(msgObj.hasOwnProperty("hp"))
			{
				this.hp = msgObj.hp;
			}
			if(msgObj.hasOwnProperty("att"))
			{
				this.att = msgObj.att;
			}
			if(msgObj.hasOwnProperty("def"))
			{
				this.def = msgObj.def;
			}
			if(msgObj.hasOwnProperty("shield"))
			{
				this.shield = msgObj.shield;
			}
			if(msgObj.hasOwnProperty("battlePower"))
			{
				this.battlePower = msgObj.battlePower;
			}
			if(msgObj.hasOwnProperty("damInc"))
			{
				this.damInc = msgObj.damInc;
			}
			if(msgObj.hasOwnProperty("damDec"))
			{
				this.damDec = msgObj.damDec;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleAttr
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}