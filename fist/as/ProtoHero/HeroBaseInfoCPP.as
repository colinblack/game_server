package com.sanguo.game.server.connectlogic.common.message.ProtoHero
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class HeroBaseInfoCPP
	{
		public static const PROTO:String = "ProtoHero.HeroBaseInfoCPP";
		public var package_root:*;
		public  var message:*;
		public var heroid:int;
		public var exp:Number;
		public var addExp:int;
		public var level:int;
		public var hp:int;
		public var att:int;
		public var def:int;
		public var first:int;
		public var hit:int;
		public var dodge:int;
		public var critStrike:int;
		public var critRate:int;
		public var critResist:int;
		public var dragonBall:int;
		public var stars:int;
		public var skill:Vector.<int>;
		public var detachUid:int;
		public var detachSlot:int;
		public var battlePower:int;
		public function HeroBaseInfoCPP(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			heroid = undefined;
			exp = undefined;
			addExp = undefined;
			level = undefined;
			hp = undefined;
			att = undefined;
			def = undefined;
			first = undefined;
			hit = undefined;
			dodge = undefined;
			critStrike = undefined;
			critRate = undefined;
			critResist = undefined;
			dragonBall = undefined;
			stars = undefined;
			skill = new Vector.<int>();
			detachUid = undefined;
			detachSlot = undefined;
			battlePower = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.heroid = this.heroid;
			if(this.exp!= undefined)
			{
				serializeObj.exp = this.exp;
			}
			if(this.addExp!= undefined)
			{
				serializeObj.addExp = this.addExp;
			}
			if(this.level!= undefined)
			{
				serializeObj.level = this.level;
			}
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
			if(this.first!= undefined)
			{
				serializeObj.first = this.first;
			}
			if(this.hit!= undefined)
			{
				serializeObj.hit = this.hit;
			}
			if(this.dodge!= undefined)
			{
				serializeObj.dodge = this.dodge;
			}
			if(this.critStrike!= undefined)
			{
				serializeObj.critStrike = this.critStrike;
			}
			if(this.critRate!= undefined)
			{
				serializeObj.critRate = this.critRate;
			}
			if(this.critResist!= undefined)
			{
				serializeObj.critResist = this.critResist;
			}
			if(this.dragonBall!= undefined)
			{
				serializeObj.dragonBall = this.dragonBall;
			}
			if(this.stars!= undefined)
			{
				serializeObj.stars = this.stars;
			}
			serializeObj.skill = [];
			for(var i:int = 0;i < this.skill.length;i++)
			{
				serializeObj.skill.push(this.skill[i]);
			}
			if(this.detachUid!= undefined)
			{
				serializeObj.detachUid = this.detachUid;
			}
			if(this.detachSlot!= undefined)
			{
				serializeObj.detachSlot = this.detachSlot;
			}
			if(this.battlePower!= undefined)
			{
				serializeObj.battlePower = this.battlePower;
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):HeroBaseInfoCPP
		{
			heroid = undefined;
			exp = undefined;
			addExp = undefined;
			level = undefined;
			hp = undefined;
			att = undefined;
			def = undefined;
			first = undefined;
			hit = undefined;
			dodge = undefined;
			critStrike = undefined;
			critRate = undefined;
			critResist = undefined;
			dragonBall = undefined;
			stars = undefined;
			skill = new Vector.<int>();
			detachUid = undefined;
			detachSlot = undefined;
			battlePower = undefined;
			this.heroid = msgObj.heroid;
			if(msgObj.hasOwnProperty("exp"))
			{
				this.exp = msgObj.exp;
			}
			if(msgObj.hasOwnProperty("addExp"))
			{
				this.addExp = msgObj.addExp;
			}
			if(msgObj.hasOwnProperty("level"))
			{
				this.level = msgObj.level;
			}
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
			if(msgObj.hasOwnProperty("first"))
			{
				this.first = msgObj.first;
			}
			if(msgObj.hasOwnProperty("hit"))
			{
				this.hit = msgObj.hit;
			}
			if(msgObj.hasOwnProperty("dodge"))
			{
				this.dodge = msgObj.dodge;
			}
			if(msgObj.hasOwnProperty("critStrike"))
			{
				this.critStrike = msgObj.critStrike;
			}
			if(msgObj.hasOwnProperty("critRate"))
			{
				this.critRate = msgObj.critRate;
			}
			if(msgObj.hasOwnProperty("critResist"))
			{
				this.critResist = msgObj.critResist;
			}
			if(msgObj.hasOwnProperty("dragonBall"))
			{
				this.dragonBall = msgObj.dragonBall;
			}
			if(msgObj.hasOwnProperty("stars"))
			{
				this.stars = msgObj.stars;
			}
			for(var i:int = 0;i < msgObj.skill.length;i++)
			{
				this.skill.push(msgObj.skill[i]);
			}
			if(msgObj.hasOwnProperty("detachUid"))
			{
				this.detachUid = msgObj.detachUid;
			}
			if(msgObj.hasOwnProperty("detachSlot"))
			{
				this.detachSlot = msgObj.detachSlot;
			}
			if(msgObj.hasOwnProperty("battlePower"))
			{
				this.battlePower = msgObj.battlePower;
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):HeroBaseInfoCPP
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}