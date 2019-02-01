package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class HerosInfo
	{
		public static const PROTO:String = "User.HerosInfo";
		public var package_root:*;
		public  var message:*;
		public var hero:Vector.<HeroBaseInfoCPP>;
		public function HerosInfo(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			hero = new Vector.<HeroBaseInfoCPP>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.hero = [];
			for(var i:int = 0;i < this.hero.length;i++)
			{
				serializeObj.hero.push(this.hero[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):HerosInfo
		{
			hero = new Vector.<HeroBaseInfoCPP>();
			for(var i:int = 0;i < msgObj.hero.length;i++)
			{
				this.hero.push(new HeroBaseInfoCPP(package_root).unserialize(msgObj.hero[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):HerosInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}