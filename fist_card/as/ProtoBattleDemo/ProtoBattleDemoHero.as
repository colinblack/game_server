package com.sanguo.game.server.connectlogic.common.message.ProtoBattleDemo
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleDemoHero
	{
		public static const PROTO:String = "ProtoBattleDemo.ProtoBattleDemoHero";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var hp:int;
		public var att:int;
		public var def:int;
		public var crit:int;
		public var acrit:int;
		public var dodge:int;
		public var adodge:int;
		public var critt:Number;
		public var speed:int;
		public var battlePower:int;
		public var skill:Vector.<ProtoBattleDemoHeroSkill>;
		public function ProtoBattleDemoHero(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			id = undefined;
			hp = undefined;
			att = undefined;
			def = undefined;
			crit = undefined;
			acrit = undefined;
			dodge = undefined;
			adodge = undefined;
			critt = undefined;
			speed = undefined;
			battlePower = undefined;
			skill = new Vector.<ProtoBattleDemoHeroSkill>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
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
			if(this.crit!= undefined)
			{
				serializeObj.crit = this.crit;
			}
			if(this.acrit!= undefined)
			{
				serializeObj.acrit = this.acrit;
			}
			if(this.dodge!= undefined)
			{
				serializeObj.dodge = this.dodge;
			}
			if(this.adodge!= undefined)
			{
				serializeObj.adodge = this.adodge;
			}
			if(this.critt!= undefined)
			{
				serializeObj.critt = this.critt;
			}
			if(this.speed!= undefined)
			{
				serializeObj.speed = this.speed;
			}
			if(this.battlePower!= undefined)
			{
				serializeObj.battlePower = this.battlePower;
			}
			serializeObj.skill = [];
			for(var i:int = 0;i < this.skill.length;i++)
			{
				serializeObj.skill.push(this.skill[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleDemoHero
		{
			id = undefined;
			hp = undefined;
			att = undefined;
			def = undefined;
			crit = undefined;
			acrit = undefined;
			dodge = undefined;
			adodge = undefined;
			critt = undefined;
			speed = undefined;
			battlePower = undefined;
			skill = new Vector.<ProtoBattleDemoHeroSkill>();
			this.id = msgObj.id;
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
			if(msgObj.hasOwnProperty("crit"))
			{
				this.crit = msgObj.crit;
			}
			if(msgObj.hasOwnProperty("acrit"))
			{
				this.acrit = msgObj.acrit;
			}
			if(msgObj.hasOwnProperty("dodge"))
			{
				this.dodge = msgObj.dodge;
			}
			if(msgObj.hasOwnProperty("adodge"))
			{
				this.adodge = msgObj.adodge;
			}
			if(msgObj.hasOwnProperty("critt"))
			{
				this.critt = msgObj.critt;
			}
			if(msgObj.hasOwnProperty("speed"))
			{
				this.speed = msgObj.speed;
			}
			if(msgObj.hasOwnProperty("battlePower"))
			{
				this.battlePower = msgObj.battlePower;
			}
			for(var i:int = 0;i < msgObj.skill.length;i++)
			{
				this.skill.push(new ProtoBattleDemoHeroSkill(package_root).unserialize(msgObj.skill[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleDemoHero
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}