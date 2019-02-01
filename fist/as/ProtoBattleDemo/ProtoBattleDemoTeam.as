package com.sanguo.game.server.connectlogic.common.message.ProtoBattleDemo
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoBattleDemoTeam
	{
		public static const PROTO:String = "ProtoBattleDemo.ProtoBattleDemoTeam";
		public var package_root:*;
		public  var message:*;
		public var hero:Vector.<ProtoBattleDemoHero>;
		public var item:Vector.<ProtoBattleDemoItem>;
		public var level:int;
		public function ProtoBattleDemoTeam(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			hero = new Vector.<ProtoBattleDemoHero>();
			item = new Vector.<ProtoBattleDemoItem>();
			level = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.hero = [];
			for(var i:int = 0;i < this.hero.length;i++)
			{
				serializeObj.hero.push(this.hero[i].serialize());
			}
			serializeObj.item = [];
			for(var i:int = 0;i < this.item.length;i++)
			{
				serializeObj.item.push(this.item[i].serialize());
			}
			serializeObj.level = this.level;
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoBattleDemoTeam
		{
			hero = new Vector.<ProtoBattleDemoHero>();
			item = new Vector.<ProtoBattleDemoItem>();
			level = undefined;
			for(var i:int = 0;i < msgObj.hero.length;i++)
			{
				this.hero.push(new ProtoBattleDemoHero(package_root).unserialize(msgObj.hero[i]));
			}
			for(var i:int = 0;i < msgObj.item.length;i++)
			{
				this.item.push(new ProtoBattleDemoItem(package_root).unserialize(msgObj.item[i]));
			}
			this.level = msgObj.level;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoBattleDemoTeam
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}