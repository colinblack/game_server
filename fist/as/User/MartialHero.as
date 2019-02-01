package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class MartialHero
	{
		public static const PROTO:String = "User.MartialHero";
		public var package_root:*;
		public  var message:*;
		public var heroInfo:Vector.<MartialHeroInfo>;
		public function MartialHero(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			heroInfo = new Vector.<MartialHeroInfo>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.heroInfo = [];
			for(var i:int = 0;i < this.heroInfo.length;i++)
			{
				serializeObj.heroInfo.push(this.heroInfo[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):MartialHero
		{
			heroInfo = new Vector.<MartialHeroInfo>();
			for(var i:int = 0;i < msgObj.heroInfo.length;i++)
			{
				this.heroInfo.push(new MartialHeroInfo(package_root).unserialize(msgObj.heroInfo[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):MartialHero
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}